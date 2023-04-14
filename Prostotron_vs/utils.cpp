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
    printf ("\t%c Welcome to the PROSTOTRON.                                %c\n", 186, 186);
    printf ("\t%c Enter commands of your program one by one.                %c\n", 186, 186);
    printf ("\t%c I will print a number of memory cell and a question       %c\n", 186, 186);
    printf ("\t%c mark (?) After that you can enter a word to that          %c\n", 186, 186);
    printf ("\t%c memory cell.                                              %c\n", 186, 186);
    printf ("\t%c Enter 'cmd' to go to command mode.                        %c\n", 186, 186);
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


void formatMemoryCellToPrint(const int cellNumP, const int cellValP, char* aTmpBuf)
{
    /**
     * Return value is in aTmpBuf array.
     */

    if (cellNumP < 10)
        aTmpBuf += sprintf(aTmpBuf, "0%d :", cellNumP);
    else
        aTmpBuf += sprintf(aTmpBuf, "%d :", cellNumP);

    if (cellValP == 0)
    {
        sprintf (aTmpBuf, "  +0000");
    }
    else if (cellValP > 0)
    {
        if (cellValP < 10)
            sprintf (aTmpBuf, "  +000%d", cellValP);
        else if (cellValP < 100)
            sprintf (aTmpBuf, "  +00%d", cellValP);
        else if (cellValP < 1000)
            sprintf (aTmpBuf, "  +0%d", cellValP);
        else if (cellValP < 10000)
            sprintf (aTmpBuf, "  +%d", cellValP);
    }
    else
    {
        if (cellValP > -10)
            sprintf (aTmpBuf, "  -000%d", cellValP * (-1) );
        else if (cellValP > -100 )
            sprintf (aTmpBuf, "  -00%d", cellValP * (-1));
        else if (cellValP > -1000)
            sprintf (aTmpBuf, "  -0%d", cellValP * (-1));
        else if (cellValP > -10000)
            sprintf (aTmpBuf, "  -%d", cellValP * (-1));
    }

    // return aTmpBuf;
}
