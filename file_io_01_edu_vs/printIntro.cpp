//============================================================
//
// Description:
// Timer class
//============================================================
#include "printIntro.h"

printIntro::printIntro() 
{ }

printIntro::~printIntro() 
{ }

void printIntro::PrintIntroduction()
{
  int i;
  int nFrame = 59;
  printf ("\t%c", 201);
  for (i=0; i<nFrame; i++)
    printf ("%c", 205);
    
    printf ("%c\n", 187);	
	printf ("\t%c The wait command is used within a computer batch file     %c\n", 186, 186);
	printf ("\t%c and allows the computer to pause the currently running    %c\n", 186, 186);
	printf ("\t%c batch file for an amount of milliseconds .                %c\n", 186, 186);
	printf ("\t%c Usage: 'WAIT 1000' will wait for 1 second.                %c\n", 186, 186);
	printf ("\t%c                                                           %c\n", 186, 186);
	printf ("\t%c                   GE (c) 2007.                            %c\n", 186, 186);

	printf ("\t%c", 200);
	for (i=0; i<nFrame; i++)
	   printf ("%c", 205);
	printf ("%c\n", 188);	

};

// End of the class.
