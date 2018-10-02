#include <stdlib.h>
#include <assert.h>

typedef unsigned int u32;
typedef unsigned long long u64;

//-------------------------------------------------------------------------
// WorkArea
//-------------------------------------------------------------------------
namespace WorkArea
{
    static const u32 circularSize = 253250;
    u32 circular[circularSize] = { 0 };         // consumes 1013000 bytes

    static const u32 stageSize = 8000;
    u32 stage[stageSize];                       // consumes 32000 bytes

    u32* headPtr = circular;
    u32 numDeltas = 0;
    u32 numStaged = 0;
}

//-------------------------------------------------------------------------
// Lookup table
//-------------------------------------------------------------------------
static const u32 LUTsize = 64;
const u32 LUT[LUTsize] = {
    0x00000000, 0x0288df0d, 0x050b5170, 0x07876772,
    0x09fd3131, 0x0c6cbea6, 0x0ed61f9d, 0x113963bd,
    0x13969a84, 0x15edd348, 0x183f1d3b, 0x1a8a8766,
    0x1cd020ad, 0x1f0ff7cc, 0x214a1b5e, 0x237e99d4,
    0x25ad817f, 0x27d6e088, 0x29fac4f7, 0x2c193cad,
    0x2e32556d, 0x30461cd1, 0x3254a056, 0x345ded53,
    0x366210ff, 0x3861186f, 0x3a5b1096, 0x3c500649,
    0x3e40063a, 0x402b1cfa, 0x421156fd, 0x43f2c095,
    0x45cf65f7, 0x47a75337, 0x497a944b, 0x4b49350b,
    0x4d134131, 0x4ed8c45a, 0x5099ca03, 0x52565d8e,
    0x540e8a41, 0x55c25b43, 0x5771dba1, 0x591d1649,
    0x5ac41611, 0x5c66e5b1, 0x5e058fc6, 0x5fa01ed4,
    0x61369d41, 0x62c9155d, 0x6457915a, 0x65e21b51,
    0x6768bd44, 0x68eb8119, 0x6a6a709d, 0x6be59584,
    0x6d5cf96c, 0x6ed0a5d9, 0x7040a435, 0x71acfdd4,
    0x7315bbf3, 0x747ae7b7, 0x75dc8a2c, 0x773aac4a
};

static const u32 bit2 = 1u << 30;

//-------------------------------------------------------------------------
// Interval
//-------------------------------------------------------------------------
struct Interval
{
    u32 lo;
    u32 range;

    Interval()             { lo = 0; range = ~0u; }
    void set(u32 l, u32 h) { lo = l; range = h - l; }
    u32 lerp(u64 x)        { return lo + (u32) ((range * x) >> 32); }
};

//-------------------------------------------------------------------------
// BitReader
//-------------------------------------------------------------------------
struct BitReader
{
    u32* readPtr;
    u32 readBit;

    BitReader()
    {
        readPtr = WorkArea::circular;
        readBit = 32;
    }

    u32 readOneBit()
    {
        u32 bit = (*readPtr >> --readBit) & 1;
        if (readBit == 0)
        {
            readBit = 32;
            if (++readPtr == WorkArea::circular + WorkArea::circularSize)
                readPtr = WorkArea::circular;
        }
        return bit;
    }
};

//-------------------------------------------------------------------------
// Decoder
//-------------------------------------------------------------------------
struct Decoder : BitReader
{
    Interval readInterval;
    u32 readSeq;
    u32 readSeqBits;

    Decoder() : BitReader()
    {
        readSeq = 0;
        readSeqBits = 1;
    }

    u32 decode()
    {
        for (; readSeqBits < 32; readSeqBits++)
            readSeq = (readSeq << 1) | readOneBit();

        u32 a = 0; 
        u32 b = LUTsize;
        u32 readRel = readSeq - readInterval.lo;
        u32 relA = 0;
        u32 relB = readInterval.range;
        while (b > a + 1)
        {
            u32 mid = (a + b) >> 1;
            u32 rel = readInterval.lerp(LUT[mid]) - readInterval.lo;
            if (readRel >= rel)
            {
                a = mid;
                relA = rel;
            }
            else
            {
                b = mid;
                relB = rel;
            }
        }

        u32 A = relA + readInterval.lo;
        u32 B = relB + readInterval.lo;
        assert(A != B);
        while ((int) (A ^ B) >= 0)
        {
            readSeqBits--;
            A <<= 1;
            B <<= 1;
        }
        if ((int) readInterval.lo >= 0)
            assert((int) A >= 0 && (int) B < 0);
        while ((A & bit2) && !(B & bit2))
        {
            readSeqBits--;
            A <<= 1;
            B <<= 1;
        }
        readInterval.set(A, B);
        return a;
    }

    u32 popDelta()
    {
        u32 value = 0;
        for (;;)
        {
            u32 t = decode();
            value += t;
            if (t < LUTsize - 1)
                return value;
        }
    }

    void reset()
    {
        readPtr = WorkArea::headPtr;
        readBit = 32;
        readInterval.set(0, ~0u);
        readSeq = 0;
        readSeqBits = 0;
    }
};

Decoder g_Decoder;

//-------------------------------------------------------------------------
// BitWriter
//-------------------------------------------------------------------------
struct BitWriter
{
    u32* writePtr;
    u32 writeBit;

    BitWriter()
    {
        writePtr = WorkArea::circular;
        writeBit = 32;
    }

    void writeOneBit(u32 bit) // 0 or 1
    {
        *writePtr |= bit << --writeBit;
        if (writeBit == 0)
        {
            writeBit = 32;
            if (++writePtr == WorkArea::circular + WorkArea::circularSize)
                writePtr = WorkArea::circular;
            if (writePtr == g_Decoder.readPtr)
                abort(); // Overflow detection
            *writePtr = 0;
        }
    }
};

//-------------------------------------------------------------------------
// Encoder
//-------------------------------------------------------------------------
struct Encoder : BitWriter
{
    Interval writeInterval;

    void addCarry()
    {
        u32* w = writePtr;
        for (u32 b = 2u << (writeBit - 1);; b <<= 1)
        {
            if (b == 0)
            {
                b = 1;
                if (--w == WorkArea::circular - 1)
                    w = WorkArea::circular + WorkArea::circularSize - 1;
            }
            *w ^= b;
            if (*w & b)
                break;
        }
    }

    void encode(u32 value)
    {
        u32 A = writeInterval.lerp(LUT[value]);
        u32 B = writeInterval.lerp(value < LUTsize - 1 ? LUT[value + 1] : 1ull << 32);

        assert(A != B);
        if ((int) writeInterval.lo < 0 && (int) A >= 0)
            addCarry();
        while ((int) (A ^ B) >= 0)
        {
            writeOneBit(A >> 31);
            A <<= 1;
            B <<= 1;
        }
        if ((int) writeInterval.lo >= 0)
            assert((int) A >= 0 && (int) B < 0);
        while ((A & bit2) && !(B & bit2))
        {
            writeOneBit(A >> 31);
            A <<= 1;
            B <<= 1;
        }
        writeInterval.set(A, B);
    }

    void pushDelta(u32 delta)
    {
        while (delta >= LUTsize - 1)
        {
            encode(LUTsize - 1); // Use the [LUT(63), 1) subinterval
            delta -= LUTsize - 1;
        }
        encode(delta);
    }

    void flush()
    {
        encode(LUTsize / 2);
        for (u32 i = 32; --i > 0;)
            writeOneBit((writeInterval.lo >> i) & 1);
        while (writeBit != 32)
            writeOneBit(0);
        writeInterval.set(0, ~0u);
    }
};

Encoder g_Encoder;

//-------------------------------------------------------------------------
// mergeStageToCircular
//-------------------------------------------------------------------------
inline int u32Compare(const u32* a, const u32* b) { return *a - *b; }
void mergeStageToCircular()
{
    using namespace WorkArea;
    qsort(stage, numStaged, 4, (int (*)(const void*, const void*)) u32Compare);

    u32 i = 0;
    u32 j = 0;
    u32 prev = 0;
    u32 iValue = i < numDeltas ? g_Decoder.popDelta() : ~0u;
    u32 jValue = j < numStaged ? stage[j] : ~0u;
    while (i < numDeltas || j < numStaged)
    {
        if (iValue < jValue)
        {
            g_Encoder.pushDelta(iValue - prev);
            prev = iValue;
            iValue = ++i < numDeltas ? iValue + g_Decoder.popDelta() : ~0u;
        }
        else
        {
            g_Encoder.pushDelta(jValue - prev);
            prev = jValue;
            jValue = ++j < numStaged ? stage[j] : ~0u;
        }
    }

    numDeltas += numStaged;
    numStaged = 0;
    g_Encoder.flush();
    g_Decoder.reset();
    headPtr = g_Encoder.writePtr;
}

//-------------------------------------------------------------------------
// main
//-------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    // Read input
    for (;;)
    {
        int value;
        if (scanf("%d", &value) != 1)
            break;
        if (WorkArea::numStaged >= WorkArea::stageSize)
            mergeStageToCircular();
        WorkArea::stage[WorkArea::numStaged++] = value;
    }
    if (WorkArea::numStaged > 0)
        mergeStageToCircular();

    // Write output
    u32 value = 0;
    for (u32 i = 0; i < WorkArea::numDeltas; i++)
    {
        value += g_Decoder.popDelta();
        printf("%08d\n", value);
    }
    return 0;
}
