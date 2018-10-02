// edu_sorting_app.cpp : Defines the entry point for the console application.
//

#include "gen.h" 
#include "cTimer.h"
#include "bubble_sort.h"
#include "RandomNumbers.h"
#include "create_array.h"

int test_()
{
   double t;
   int const size=500;
   int mass[size];
   // randomize();
   for (int i=0; i<size; i++)
   {
      // mass[i]=random(20000)-10000;
      cout  <<'\n' << mass[i]<<"||";
      cout << '\t';
   }
   for (int j=0; j<size; j++)
 
        for (int i=1; i<size; i++)
 
        if (mass[i]<mass[i-1])
        {
            t=mass[i];
            mass[i]=mass[i-1];
            mass[i-1]=t;    
        }
        for (int i=0; i<size; i++)
        {
             cout << '\t' << mass[i];
        } 
   
   getch();
   return 0;
}

int main(int argc, char *argv[], char *envp[]) 
{
    int RValue = false;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;
    int arraySize = 2000;

    printf ("main - start\n");
    CTimer *_time = new CTimer ();

    Create_RND_Array *_rnd_array = new Create_RND_Array();

    // bubble_sort();
    // saveRandomNumbers(arraySize);
    _rnd_array->save_to_file(arraySize);
    bubble_sort_optim(arraySize);
    
//*************MAIN LOOP*****************//
cout << "\n $> Press Ctr-X to exit." << std::endl;
do 
{
    //This is simple Windows way:
    Sleep(100);
   
   
   //nResult = produceRND();   
   //printf ("1-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);
   
   //nResult = produceRND();   
   //printf ("2-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);

   // control of endless loop (may be also in monitor.cpp)
    if (_kbhit())  // has anything been pressed from keyboard ?
    {
        NewChar=(unsigned char)_getch();  
        RValue = true;
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
} while (!RValue);  
printf ("Application complete.\n");
return 0;
}
