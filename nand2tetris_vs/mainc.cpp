#include "gen.h"
#include "utils.h"
#include "nand.h"

#define B00000000 0
#define B00000001 1
#define B00000010 2

long g_lTimeTick = 0;

void test_not()
{
    NOT* not = new NOT();
    
    not->in = 0;
    not->run();
    printf("not(%d) out=%d\n", not->in, not->out);

    not->in = B00000001;
    not->run();
    printf("not(%d) out=%d\n", not->in, not->out);
}


void test_nand()
{
    NAND* nand = new NAND();
    nand->a = 0;
    nand->b = 0;
    nand->run();
    printf("nand out=%d\n", nand->out);

    nand->a = 0;
    nand->b = 1;
    nand->run();
    printf("nand out=%d\n", nand->out);

    nand->a = 1;
    nand->b = 0;
    nand->run();
    printf("nand out=%d\n", nand->out);

    nand->a = 1;
    nand->b = 1;
    nand->run();
    printf("nand out=%d\n", nand->out);
}


int main(int argc, char *argv[], char *envp[]) 
{
    long LastTimeIn=0;    
    long LastTimeInMS = 0;    
    int RValue = false;
    int Counter=0;  
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;

    printf ("main - start\n");
    
#ifdef FILE_OUTPUT
    int nOpenFileToken = 0;
    char *FileNameF = "TimeSt.log";
    FILE *fi = NULL; 
 
 // open the file for input:    
 if ( (fi = fopen(FileNameF, "a+") ) != NULL)
  {
  // printf ("file %s was open succesfully\n", FileNameF);
   nOpenFileToken = 1;
  }
 else
  {
   printf ("file %s was not open\n", FileNameF);
   getchar(); // pause, xyLe...
   nOpenFileToken = 0;
  }
      
  fprintf(fi, "Start time: %d\n", Get1msTime());
#endif// FILE_OUTPUT

if (argc >= 2)
{
  // i = atoi(argv[1]);
  if ( (strcmp(argv[1], "/?") ==0) || (strcmp(argv[1], "-?") ==0) || (strcmp(argv[1], "help") ==0) )
  {
   PrintIntroduction();
   return 1;
  }
}
 /*
    NAND* nand = new NAND();
    nand->a = 0;
    nand->b = 0;
    nand->run();
    printf("nand out=%d\n", nand->out);
*/
    test_nand();
    test_not();
 //*************MAIN LOOP*****************//
 do 
 {
   //This is simple Windows way:
   Sleep(1000);
     
 /*
 // This is complicated one-thread way:
  if ((( Get1msTimeMS() - LastTimeInMS)>1000-1) || (LastTimeInMS > Get1msTimeMS() ))
    {    
     printf ("Time: %ld.\n",Get1msTimeMS());
     Sleep(100);
           
     LastTimeInMS = Get1msTimeMS();
   }   
*/

  // control of endless loop (may be also in monitor.cpp)
    if (kbhit())  // has anything been pressed from keyboard ?
    {
        RValue = true;

        NewChar=(unsigned char)getch();
        if ((NewChar & 0xff) == 24)  // CTRL-X   pressed
        {
            RValue = true; // END mark
        }
        if (NewChar == 'd')  // pressed
        {
        if (1 == CaptureModeHex) 
            CaptureModeHex = 1;
            else
                CaptureModeHex = 0;
        }
    }   

}while (!RValue);  

#ifdef FILE_OUTPUT
 if (1 == nOpenFileToken)
   fclose (fi);
#endif
 
printf ("Application complete.\n");
return 0;
}

