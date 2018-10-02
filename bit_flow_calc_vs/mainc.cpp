#include <stdio.h>
#include <string.h>
#include "gen.h"
#include "dos.h"
#include <stdlib.h>
#include "utils.h"
#include "dbits.h"

int main( int argc, char *argv[] )
{
    const int bit_val = 4;
    unsigned char buffer[bit_val+1];
    int i=0;

// #define YS9039384
#ifdef YS9039384
    char* FileNameF = "Result.log";
    FILE *fi = NULL;
#endif

    // double Res = 132316.5;
    // Res = 549755813.0;
    //int Res = -1<<4;
    //int Res = 1<<7;
    // int Res = 10;
    //printf ("Res = %f\n", Res);
    float Res = 1.1;
    ufloat u1;
    u1.f = Res;
    dispBits(u1.u, 1);
    
    printf ("sizeof(Res) = %d\n", sizeof(Res) ); 
    printf ("dispBits(%d):", Res); 
    dispBits(Res, 1);
    printf ("\n-----------"); 
    
    memcpy((void *)(buffer), (const void*)&Res, sizeof(Res));

    // for (i=0; i<bit_val; i++)
    for (i=bit_val-1; i>=0; i--)
    {
        printf ("\n[%d] = 0x%X - ", i, buffer[i]);
        // dispBitsToFile(buffer[i], "BinHex.log");
        dispBits(buffer[i], 1);
    }

    printf ("\nnumber %ld in Hex format:\n", Res);
    for (i=bit_val-1; i>=0; i--)
    // for (i=0; i<bit_val; i++)
    {
        printf ("0x%X ", buffer[i]);
        //dispBitsToFile(buffer[i], "BinHex.log");
        //dispBits(buffer[i], 1);
    }

    printf ("\nnumber %0.2f in binary format:\n", Res);
    // for (i=0; i<bit_val; i++)
    for (i=bit_val-1; i>=0; i--)
    {
        // printf ("0x%X ", buffer[i]);
        //dispBitsToFile(buffer[i], "BinHex.log");
        dispBits(buffer[i], 1);
    }

#ifdef YS9039384
    if ( (fi = fopen(FileNameF, "a+") ) != NULL)
    {
        fclose (fi);
    }
#endif
    printf ("\n");
    system ("PAUSE");
    return 0;
}

