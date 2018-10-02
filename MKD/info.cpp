#include <stdio.h>
#include "info.h"
#include "gen.h"
		
#ifdef ZPCHECK		
void PrintIntroduction(int hlp)
{
  int i;
  int nFrame = 59;
	printf ("\n");
	printf ("\t%c", 201);
	for (i=0; i<nFrame; i++)
	   printf ("%c", 205);
    printf ("%c\n", 187);	
   if (1==hlp)
    printf ("\t%c The application will work according to the data you       %c\n", 186, 186);
   else if (2==hlp)
    printf ("\t%c Sorry, but program can not accept too few parameters you  %c\n", 186, 186);
   else
    printf ("\t%c Sorry, but program can not run with this data you         %c\n", 186, 186);
	
	printf ("\t%c give for it. Please, check the input parameters.          %c\n", 186, 186);
	printf ("\t%c Actually, it has to be in follow order:                   %c\n", 186, 186);
	printf ("\t%c     zpcheck.exe <KEY> <zip_file_name> <info_file_name>    %c\n", 186, 186);
	printf ("\t%c Where: KEY - COMPARE or WRITE; zip_file_name is a file    %c\n", 186, 186);
	printf ("\t%c you want to check it's timestamp, info_file_name - a file %c\n", 186, 186);
	printf ("\t%c where you can read/write a timestamp to compare.          %c\n", 186, 186);
	printf ("\t%c Good luck.                                                %c\n", 186, 186);	
	printf ("\t%c", 200);
	for (i=0; i<nFrame; i++)
	   printf ("%c", 205);
  printf ("%c\n", 188);	
}
#endif // ZPCHECK	

#ifdef MKD		
void PrintIntroduction(int hlp)
{
  int i;
  int nFrame = 59;
	printf ("\n");
	printf ("\t%c", 201);
	for (i=0; i<nFrame; i++)
	  printf ("%c", 205);
    printf ("%c\n", 187);	
   if (1==hlp)
    printf ("\t%c The application will work according to the data you       %c\n", 186, 186);
   else if (2==hlp)
    printf ("\t%c Sorry, but program can not accept too few parameters you  %c\n", 186, 186);
   else
    printf ("\t%c Sorry, but program can not run with this data you         %c\n", 186, 186);
	
	printf ("\t%c give for it. Please, check the input parameters.          %c\n", 186, 186);
	printf ("\t%c Actually, it has to be in follow order:                   %c\n", 186, 186);
	printf ("\t%c     mkd.exe <KEY> <filename> <message_to_file>            %c\n", 186, 186);
	printf ("\t%c Where: KEY - ADD or WRITE;                                %c\n", 186, 186);
	printf ("\t%c If use key WRITE, mkd.exe will write 'call backup.bat' +  %c\n", 186, 186);
  printf ("\t%c today's timestamp + message in one line                   %c\n", 186, 186);
	printf ("\t%c If use key ADD, mkd.exe will write today's timestamp and  %c\n", 186, 186);
  printf ("\t%c the <message_to_file> in 2 lines to the <filename>        %c\n", 186, 186);
	printf ("\t%c Good luck.                                                %c\n", 186, 186);	
	printf ("\t%c", 200);
	for (i=0; i<nFrame; i++)
	   printf ("%c", 205);
  printf ("%c\n", 188);	
}
#endif // MKD

