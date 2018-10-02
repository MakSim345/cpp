#include <stdio.h>
#include <string.h>
#include "gen.h"
#include <stdlib.h>
#include "utils.h"
#include "dbits.h"
#include "cube_calc.h"

// #define YS9039384

#define TMON_MAX_JSON_LENGTH 25

// UTF-16 style characters
typedef unsigned short Utf16Char;


typedef struct tagTraceJsonCommandPacket
{
    int          hdr;
    char    texts[TMON_MAX_JSON_LENGTH];
} TraceMonJsonCommandPacket;


void run()
{
    TraceMonJsonCommandPacket packet;
    char buffer[TMON_MAX_JSON_LENGTH];
    // packet.texts 
    
    string tmp = "Smart red fox jumps\n";    
    strcpy(packet.texts, tmp.c_str());        

    printf("--------run starts:\n");

    // memcpy((void *)(buffer), (const void*)&packet.texts, sizeof(packet.texts));

    // for (int i=0; i<sizeof(packet.texts) - 1; i++)
    for (int i=0; i < 20; i++)
    {
        // printf ("[%d] = 0x%X\n", i, buffer[i]);
        // printf ("[%d]:%c(0x%X), ", i, packet.texts[i], packet.texts[i]);
        buffer[i] = packet.texts[i];
        //int n, a=5, b=3;
        //n = sprintf (buffer, "%d plus %d is %d", a, b, a+b);
        // printf ("[%s] is a string %d chars long\n",buffer,n);
        // 
    }
    printf ("[%s] is a string\n", buffer);
}


void mem_addr()
{
    int rat = 10323;
    int & rod = rat;

    printf ("rat = %d\n", rat);
    printf ("rod = %d\n", rod);
    
    cout << "rat address: 0x" << &rat << "\n";
    cout << "rod address: 0x" << &rod << "\n";

}

int main( int argc, char *argv[] )
{

    // run();
    mem_addr();
    printf("\nApp end.\n");
    return 0;
}


