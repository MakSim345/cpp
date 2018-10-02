#include "gen.h"
#include "utils.h"
#include "RandomNumbers.h"
#include "cTimer.h"
#include "person.h"
#include "cross_reference.h"
#include "derived_class.h"

bool validateStudent(Student &_person_to_check)
{
    return _person_to_check.amIStudent();
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

    std::cout << "main - start\n";    
    
    CTimer *_time = new CTimer();

    // test virtual classes:
    // Person *newPers = new Student();
    Student *newPers = new Student();
    
    validateStudent(*newPers);

        
 cout << std::endl << "Press Ctr-X to exit." << std::endl;
 //*************MAIN LOOP*****************//
 do 
 {
   //This is simple Windows way:
   Sleep(100);
   
   nResult = produceRND();   
   // printf ("1-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);
   // printf ("%d; ", nResult);
   
   //nResult = produceRND();   
   //printf ("2-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);

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
    if (_kbhit())  // has anything been pressed from keyboard ?
    {       
     RValue = true;
     NewChar=(unsigned char)_getch();
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

