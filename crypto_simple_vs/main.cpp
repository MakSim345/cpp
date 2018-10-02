#include <stdio.h>
//#include <conio.h>
#include "Binary.h"
#include <stdlib.h>

void printInfoMessage()
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
    printf ("\t%c  Welcome to the Coding World!                             %c\n", 186, 186);
    printf ("\t%c  Now the file will be coded or decoded according          %c\n", 186, 186);
    printf ("\t%c  to the KEY you had set in the BAT file.                  %c\n", 186, 186);
    printf ("\t%c  It may take some time - depends of the file's size,      %c\n", 186, 186);
    printf ("\t%c  so please, try to be patient. After program complete,    %c\n", 186, 186);
    printf ("\t%c  you will see an appropriate message and value of bytes   %c\n", 186, 186);
    printf ("\t%c  which been changed.                                      %c\n", 186, 186);
    printf ("\t%c  Good luck.                                               %c\n", 186, 186);
    
    printf ("\t%c", 200);
    
    for (i=0; i<nFrame; i++)
    {
       printf ("%c", 205);
    }
    
    printf ("%c\n", 188);    

};

void printErrorMessage()
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
    printf ("\t%c  Welcome to the Coding World!                             %c\n", 186, 186);
    printf ("\t%c  I'm sorry, but program can not run with the data you     %c\n", 186, 186);
    printf ("\t%c  give for it. Please, check the input parameters.         %c\n", 186, 186);
    printf ("\t%c  Actually, it has to be like follow:                      %c\n", 186, 186);
    printf ("\t%c  dcript.exe <KEY> <source_file> <dest_file> [Print_info]  %c\n", 186, 186);
    printf ("\t%c  Where: KEY - is your coding key; sourse file is a text   %c\n", 186, 186);
    printf ("\t%c  you want to hide, dest - is a result file; [Print_info]  %c\n", 186, 186);
    printf ("\t%c  is an additional parameter and do not use it at all:-)   %c\n", 186, 186);
    printf ("\t%c  Good luck.                                               %c\n", 186, 186);
    
    printf ("\t%c", 200);
    
    for (i=0; i<nFrame; i++)
    {
        printf ("%c", 205);
    }
    
    printf ("%c\n", 188);    
    printf ("\nApplication complete. There was 0 iterations\n");
};

int main (int argc, char *argv[])
{
    FILE *fileInput = NULL;
    FILE *fileOutput = NULL;
    char *charFromCryptKey;
    int c;
    int nPrintValue = 0;
    long charCounter = 0;
    
    // system("app.exe");

    if (argc <= 1)
    {
       printErrorMessage();
       return 0;
    }
    else 
    {
       printInfoMessage();
    }

    if (argv[4] == NULL)
    {
       nPrintValue = 0;
    }
    else // if (argv[4] == 1)
    { 
       nPrintValue = 1;
       printf ("argv[4] =%d\n",argv[4]);
    }
 
    charFromCryptKey = argv[1];
    
    if (nPrintValue)
    {
        printf ("Program started. cp = %d (", *charFromCryptKey);
    }
    else 
    {
       printf ("Program started.\n");
    }

    dispBits((unsigned int) *charFromCryptKey, 0);
 
    if ((charFromCryptKey = argv[1]) && *charFromCryptKey != '\0') 
    {
        if ((fileInput = fopen(argv[2], "rb")) != NULL) 
        {
            if ((fileOutput = fopen(argv[3], "wb")) != NULL) 
            {
                while ((c= getc(fileInput)) != EOF)
                {
                    if (nPrintValue)
                    {
                        printf ("c = %d, *cp = %d\n", c, *charFromCryptKey);
                    }
                    
                    if (!*charFromCryptKey)
                    {
                        charFromCryptKey = argv[1];
                    }
                    
                    //printf ("before XOR: c = %d\n", c);
                    dispBits((unsigned)c, nPrintValue);
                    c^= *(charFromCryptKey++);
                    //printf ("after XOR: c = %d\n", c);
                    dispBits((unsigned)c, nPrintValue);
                    putc(c, fileOutput); 
                    charCounter++;
                }
                fclose (fileOutput);
            }
            fclose (fileInput);
        } 
    }
    printf ("\nApplication complete. There was %d iterations\n", charCounter);
	system("PAUSE");
    return 0;
}
