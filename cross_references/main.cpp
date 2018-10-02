#include "gen.h"
#include "utils.h"
#include "cross_reference.h"
#include "derived_class.h"

int main(int argc, char *argv[], char *envp[]) 
{
    long LastTimeIn=0;    
    long LastTimeInMS = 0;    
    int RValue = false;
    int Counter=0;  
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;

    std::cout << "main - start\n";    
    

    return 0;

        
 cout << std::endl << "Press Ctr-X to exit." << std::endl;
//*************MAIN LOOP*****************//
do 
{
   //This is simple Windows way:
   Sleep(100);
   
   // nResult = produceRND();   

  // control of endless loop (may be also in monitor.cpp)
   if (_kbhit())  // has anything been pressed from keyboard ?
   {
       NewChar=(unsigned char)_getch();
       RValue = true;            
   } 
}while (!RValue);  

#ifdef FILE_OUTPUT
 if (1 == nOpenFileToken)
   fclose (fi);
#endif
 
printf ("Application complete.\n");
return 0;
}

