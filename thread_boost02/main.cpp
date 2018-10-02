#include "stdafx.h"
#include "utils.h"
#include <string>
#include <stdlib.h>
//#include "myThread.h"
//#include "thWorker.h"

//#include <boost/program_options.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>

using namespace std;
using namespace boost;

void hello()
{
    // my own thread routine
    int i = 0;
    int number = 1;
    int maxNumber = 100;
    // while (1)
    for (i=0; i < maxNumber; i++)
    {
        //Sleep(100);
        // i++;
        // gVariable++;
        // ChangeFlag(0);
        printf ("Thread %d is running (%d) time.\n", number, i);
    }
    printf ("Thread %d made %d iterations\n", number, i);
    // std::cout << "Hello world, I'm a thread!" << std::endl;
}

int getRND(int minVal, int nMaxVal)
{
    int nRetVal=0;
    static int nFirstTime = 1;

    if (1 == nFirstTime)
    {
        srand (time (NULL));
        nFirstTime = 0;
    }
    int RND=rand();
    
    printf("RND: %d\n", RND);

    nRetVal = minVal + (RND % nMaxVal);
    
    printf("nRetVal: %d", nRetVal);
    return nRetVal;
}
/*
void my_worker()
{
    const int _number_of_threads = 2;
    int gVariable = 0;
    printf ("Before gVariable = %d\n", gVariable);
    MyThread *mTh[_number_of_threads];

    int pVariable = 10;

    for (int t = 0; t < _number_of_threads; t++)
    {
        mTh[t] = new MyThread(t);
        mTh[t]->getFlag(&pVariable);
        // mTh[t]->CopyVariable(pVariable);
        mTh[t]->start();
    }

    printf ("After pVariable = %d\n", pVariable);
}
*/
static int counter;

void worker()
{
    int i;
    for (i = 1; i <= 10; i++)
    {
        counter++;
    }
}

/*
void* f(void *p)
{
    worker();
}
*/

int main(int argc, _TCHAR* argv[])
{
    int NewChar=0;
    long LastTimeInMS = 0;    
    int RValue = false;

  //*********************TEST MODULE**************
    
    // printf ("Before gVariable = %d\n", gVariable);
    // boost::thread hello_thrd(&hello);
    // hello_thrd.join();
    // return 0;

    int i;
    int r[22] = {};
    int _ctr = 1000; // 1000000
    for(i = 0; i < _ctr  && counter != 2; ++i)
    {
        printf ("Enter to loop number = %d\n", i);
        // boost::pthread_t t1, t2;
        boost::thread t1 (worker);
        boost::thread t2(worker);
        counter = 0;
        //pthread_create(&t1, NULL, f, NULL);
        //pthread_create(&t2, NULL, f, NULL);

        //pthread_join(t1, NULL);
        //pthread_join(t2, NULL);
        t1.join();
        t2.join();
        ++r[counter];
    }

    for(i = 0; i < 22; ++i)
    {
        printf("%d:\t%d\n", i, r[i]);
    }


    //std::cout << "main: startup" << std::endl;
    //thWorker w(612, 10, 5);
    //boost::thread workerThread(w);
    //std::cout << "main: waiting for thread" << std::endl;

    //workerThread.join();

    std::cout << "main: done" << std::endl;

    // return 0;

//*************MAIN LOOP*****************//
do 
{    
    if ((( Get1msTimeMS() - LastTimeInMS)>100-1) || (LastTimeInMS > Get1msTimeMS() ))
    {
        // printf ("Time: %ld\n",Get1msTimeMS());
        printf ("%c", '.');
        LastTimeInMS = Get1msTimeMS();
    }   
    
    // control of endless loop (may be also in monitor.cpp)
    if (_kbhit())  // has anything been pressed from keyboard ?
    {
       RValue = true;
       NewChar=(unsigned char)_getch();
    }

} while (!RValue);  

std::cout << "\nApplication complete.\n";

return 0;
}
