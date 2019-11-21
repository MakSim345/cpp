#include "utils.h"

void PrintIntroduction()
{
    int i;
    int nFrame = 59;
    printf ("\n");
    printf ("\t%c", 201);
    for (i=0; i<nFrame; i++)
    {
       printf ("%c", 205);
    }
    printf ("%c\n", 187);
    printf ("\t%c Welcome to the PROSTOTRON!                                %c\n", 186, 186);
    printf ("\t%c Please, enter one by one commands of                      %c\n", 186, 186);
    printf ("\t%c your program. I will print numbers of                     %c\n", 186, 186);
    printf ("\t%c memory's cell and question mark (?)                       %c\n", 186, 186);
    printf ("\t%c After this you can enter a word to this                   %c\n", 186, 186);
    printf ("\t%c memory cell. Enter 'cmd' to go to command mode.           %c\n", 186, 186);
    printf ("\t%c Type '/?' for help screen                                 %c\n", 186, 186);

    printf ("\t%c", 200);
    for (i=0; i<nFrame; i++)
       printf ("%c", 205);
    printf ("%c\n", 188);
};

void PrintHelpInfo(int is_asm)
{
    int i;
    int nFrame = 59;
    printf ("\n");
    printf ("\t%c", 201);
    for (i=0; i<nFrame; i++)
    {
       printf ("%c", 205);
    }
    printf ("%c\n", 187);
    if (1 == is_asm)
    {
        printf ("\t%c This is HELP screen for Postotron                         %c\n", 186, 186);
        printf ("\t%c - command 'cmd' move you to command mode                  %c\n", 186, 186);
    }
    else
    {
        printf ("\t%c - command 'run' will start you program                    %c\n", 186, 186);
        printf ("\t%c - command 'trace' will start you program in trace mode    %c\n", 186, 186);
        printf ("\t%c - command 'asm' will go to assembler mode                 %c\n", 186, 186);
        printf ("\t%c - command 'save <file>' save current dump to file         %c\n", 186, 186);
        printf ("\t%c - command 'load <file>' will load a dump from file        %c\n", 186, 186);
        printf ("\t%c - command 'dir' will show list of files for load          %c\n", 186, 186);
    }
    printf ("\t%c - command 'dump' will print a memory dump                 %c\n", 186, 186);
    printf ("\t%c - command 'exit' / 'quit' will stop Postotron             %c\n", 186, 186);
    printf ("\t%c", 200);
    for (i=0; i<nFrame; i++)
    {
       printf ("%c", 205);
    }
    printf ("%c\n", 188);
};


// char * formatMemoryCellToPrint(int nClNum, int nClVal)
void formatMemoryCellToPrint(int nClNum, int nClVal, char* tmpbuf)
{
    // char tmpbuf[20];

    // sprintf(tmpbuf, "%s", cInput.c_str() + PRINT_LEN);
    // tmpbuf += sprintf( tmpbuf, "0%d :", nClNum);
    
    if (nClNum < 10)
        tmpbuf += sprintf( tmpbuf, "0%d :", nClNum);
    else
        tmpbuf += sprintf( tmpbuf, "%d :", nClNum);

    if (nClVal == 0)
    {
        sprintf (tmpbuf, "  +0000");
    }
    else if (nClVal > 0)
    {
        if (nClVal < 10)
            sprintf ( tmpbuf, "  +000%d", nClVal);
        else if (nClVal < 100)
            sprintf ( tmpbuf, "  +00%d", nClVal);
        else if (nClVal < 1000)
            sprintf ( tmpbuf, "  +0%d", nClVal);
        else if (nClVal < 10000)
            sprintf ( tmpbuf, "  +%d", nClVal);
    }
    else
    {
        if (nClVal > -10)
            sprintf ( tmpbuf, "  -000%d", nClVal *(-1) );
        else if (nClVal > -100 )
            sprintf ( tmpbuf, "  -00%d", nClVal *(-1));
        else if (nClVal > -1000)
            sprintf ( tmpbuf, "  -0%d", nClVal *(-1));
        else if (nClVal > -10000)
            sprintf ( tmpbuf, "  -%d", nClVal *(-1));
    }

    // return tmpbuf;
}
