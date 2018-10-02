//
#include "processor.h"


//*****************************************
// Class Processor implementation

void Processor::runProgramInMemory(int traceP)
    /*
      MemCell* memory //pointer to an array!,
      Processor* pProc,
      int Trace*/
{
    int  StopFlag = 0;
    std::string cInput("0");
    std::string cInTrace("0");

    mIsTrace = traceP;
    setInstructionCounter(START_ADDRESS); // set counter to the start == 0

    do
     {
        // copy next memory cell to the instruction register IR:
        this->setInstructionRegister(mMemory->getCellValue(this->getInstructionCounter()) );
        // get an operation code and operand from IR:
        this->decodeInstruction();
        // save an address of memory cell where data is:
        mMemory->setCellCounter(getOperand());

        if (mIsTrace)
        {
            mMemory->printMemoryDump ();
            this->printProcessorState();
            std::cout << "\nPress Enter to TRACE >> ";
            std::getline (std::cin, cInTrace);
        }

        switch ( this->getOpCode() )
        {
         case READ: // 10 - read a word from the terminal to the memory cell
            std::cout << " Enter value: > ";
            std::getline (std::cin, cInput);

            mMemory->setCellValue(cInput.c_str()); //
            this->incInctructionCounter();
            break;

         case WRITE:// 11 - print a word from the memory cell to the terminal
            // memory->PrintCurCellNumber();
            printf ("\nOutput: \n");
            printf ("*******************************************************\n");
            mMemory->printCellValue();
            printf ("\n*******************************************************\n");
            this->incInctructionCounter();
            break;

         case LOAD: // 20 - save a word from the memory cell to an accumulator
            this->setAccumulator( mMemory->getCellValue() );
            this->incInctructionCounter();
            break;

        case STORE: // 21 - //save a word from accumulator to memory cell
            mMemory->setCellValue(this->getAccumulator());
            this->incInctructionCounter();
            break;

         case ADD:
            this->setAccumulator(this->getAccumulator() + mMemory->getCellValue());
            this->incInctructionCounter();
            break;

         case SUBTRACT:
            this->setAccumulator(this->getAccumulator() - mMemory->getCellValue()); //
            this->incInctructionCounter();
            break;

         case DIVIDE:
            if (this->getAccumulator() == 0)
            {
                printf ("ERROR: divide to zero!\n");
                printf ("Program complete by error.\n");
                StopFlag = 1;
            }
            else
            {
                this->setAccumulator(mMemory->getCellValue() / this->getAccumulator());
            }
            this->incInctructionCounter();
            break;

         case MULTIPLY:
            this->setAccumulator(this->getAccumulator() * mMemory->getCellValue()); //
            this->incInctructionCounter();
            break;

         case BRANCH: //GOTO
            this->setInstructionCounter(getOperand());
            break;

         case BRANCHNEG: // branch if accumulator is negative
            if (this->getAccumulator() < 0)
                this->setInstructionCounter(getOperand());
            else
                this->incInctructionCounter();
            break;

         case BRANCHZERO:
            if (this->getAccumulator() == 0)
                this->setInstructionCounter(getOperand());
            else
                this->incInctructionCounter();
            break;

         case HALT:
            printf ("Program complete.\n");
            StopFlag = 1;
            break;

         default:
            printf ("Unexpected value in the address %d\n", getOperand());
            StopFlag = 1;
        }// case

        if (mIsTrace)
        {
          //mMemory->printMemoryDump ();
          //this->printProcessorState();
          //printf("\nPress Enter to TRACE >> ");
          //gets_s(cInTrace);
        }

    } while (!StopFlag);

    mMemory->printMemoryDump ();
    this->printProcessorState();

};
// constructor / destructor:
Processor::Processor()
    : mIsTrace(0)
{
    setAccumulator(0);
    setInstructionCounter(0);
    setInstructionRegister(0);
    setOpCode(0);
    setOperand(0); // this is an address of cell in the current command
}

Processor::~Processor()
{
    //printf ("destructor called!\n");
}

void Processor::decodeInstruction()
{
    setOpCode(mInstructionRegister / 100);
    setOperand(mInstructionRegister % 100);
}

void Processor::printProcessorState()
{
    printAccumulator();
    printInstructionCounter();
    printInstrRegister();
    printOpCode();
    printOperand();
}

void  Processor::setAccumulator (int nAccum)
{
    mAccumulator = nAccum;
}

int  Processor::getAccumulator ()
{
    return mAccumulator;
}

void Processor::printAccumulator()
{
    printf ("- Accumulator  = %d\n", mAccumulator );
}

void Processor::setInstructionCounter(int newInstrCtrP)
{
    mInstructionCounter = newInstrCtrP;
}

int Processor::getInstructionCounter()
{
    return mInstructionCounter;
}

void Processor::printInstructionCounter()
{
    printf ("- InctrCounter = %d\n", mInstructionCounter);
}

int Processor::incInctructionCounter()
{
    return mInstructionCounter++;
}

void Processor::setInstructionRegister(int newInsRegP)
{
    mInstructionRegister = newInsRegP;
}

int Processor::getInstructionRegister()
{
    return mInstructionRegister;
}

void Processor::printInstrRegister()
{
    printf ("- InstrRegister= %d\n", mInstructionRegister);
}

void Processor::setOpCode(int newOpCodeP)
{
    mOpCode = newOpCodeP;
}

int  Processor::getOpCode()
{
    return mOpCode;
}

void Processor::printOpCode()
{
    printf ("- OpCode       = %d, %s\n", mOpCode, getOpCodeDesctiption(mOpCode).c_str());
}

void Processor::setOperand(int newOperandP)
{
    mOperand = newOperandP;
}

int  Processor::getOperand()
{
    return mOperand;
}

void Processor::printOperand()
{
    printf ("- Operand      = %d\n", mOperand);
}

std::string Processor::getOpCodeDesctiption(int _opCode)
{
    static std::map<int, std::string> OpCodeMap;
    if(OpCodeMap.empty()) // Only runs once.
    {
        OpCodeMap[10] = "READ - from terminal to selected memory address";
        OpCodeMap[11] = "WRITE - print in terminal value of selected memory";
        OpCodeMap[20] = "LOAD - from selected memory address to accumulator";
        OpCodeMap[21] = "SAVE - from accumulator to selected memory address";
        OpCodeMap[30] = "ADD - number from selected memory address and accumulator. Result to accumulator";
        OpCodeMap[31] = "SUBTRACT - number from selected memory address and accumulator. Result to accumulator";
        OpCodeMap[32] = "DIVIDE - number from selected memory address and accumulator. Result to accumulator";
        OpCodeMap[33] = "MULTIPLY - number from selected memory address and accumulator. Result to accumulator";
        OpCodeMap[40] = "BRANCH - GoTo selected memory address, unconditional";
        OpCodeMap[41] = "BRAMCHNEG - GoTo selected memory address, if accumulator is negative";
        OpCodeMap[42] = "BRANCHZERO - GoTo selected memory address, if accumulator is zero";
        OpCodeMap[43] = "HALT - full stop";
    }
    return OpCodeMap[_opCode];
}
