// edu_sorting_app.cpp : Defines the entry point for the console application.
//

#include "gen.h"
#include "cTimer.h"
#include "bubble_sort.h"
#include "RandomNumbers.h"
#include "create_array.h"

int main(int argc, char *argv[], char *envp[])
{
    int RValue = false;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;
    int mainLoopCtr = 0;
    const int mainLoopMax = 10;
    const int arraySize = 2000;

    printf ("main - start\n");
    // CTimer *_time = new CTimer ();

    create_array *rRndArray = new create_array();

    // bubble_sort();
    // saveRandomNumbers(arraySize);
    rRndArray->save_to_file(arraySize);
    // cout << "start to sort array of " << arraySize << " \n";
    bubble_sort_optim(arraySize);
    cout << "\n\nsort array of " << arraySize << " items take " << std::clock() << " msec. \n";

//*************MAIN LOOP*****************//
cout << "\n $> Press Ctr-X to exit." << std::endl;
do
{
#ifdef WIN32_APP
    //This is simple Windows way:
    // Sleep(100);
    std::this_thread::sleep_for(100ms);
#else
    //This is simple UNIX way:
    // sleep(1);

    // standard for all OS:
    std::this_thread::sleep_for(100ms);
#endif

    printf ("0-Time: %d.\n", mainLoopCtr);

    nResult = produceRND();
    printf ("1-Time: %d. RND: %d\n", mainLoopCtr, nResult);

    nResult = produceRND();
    printf ("2-Time: %d. RND: %d\n", mainLoopCtr, nResult);

    // control of endless loop (may be also in monitor.cpp)
    mainLoopCtr++;

    if (mainLoopCtr >= mainLoopMax)
    {
        RValue = true; // END mark
    }

} while (!RValue);

#define USE_PAUSE_OR_BUTTON_PRESS
#ifdef USE_PAUSE_OR_BUTTON_PRESS
    std::cout << "\nPress ENTER to exit...\n";
    cin.get();
#endif

    printf ("Application complete.\n");
    return 0;
}


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
    {
     for (int i=1; i<size; i++)
     {
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
     }
    }
    // getch();
    return 0;
}
