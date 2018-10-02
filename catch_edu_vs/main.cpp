//
#include "gen.h" 
#include "div_error.h"
#include "my_exceptions.h"
#include "printHex.h"
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <signal.h>

#include <iostream>
#include <vector>
#include <math.h>
// #include <cmath>

using namespace std;

int memento() // handle Segfault
{
    MessageBoxA(NULL,"Memento Mori","Exception catched!",NULL);
    return 0;
}

void fault_simple() // segfault generation
{
      int *p = 0x00000000;   
      p[0] = 13;
}

void fall() // segfault generation
{
    const int _m_size = 12;
    int _m_array[_m_size];
    for (int i = 0; i<_m_size+12; i++)
    {
        //int a=rand() % my_array.size();
        _m_array[i] = rand() % _m_size;
        cout << i <<  " - " << _m_array[i];
        cout << "\n";
    }
    cout << endl;
}

void segfault() 
{
    int nFNameLen = 12;
    char *m_FileNameF = new char[nFNameLen];
    const char* ClassFileNaMe = "allegro.log";
    sprintf(m_FileNameF, ClassFileNaMe);
    delete [] m_FileNameF;
}

void posix_death_signal(int signum)
{
    memento();
    signal(signum, SIG_DFL);
    exit(3);
}

float quotient(int num1, int num2)
{
    if (num2==0)
    {
        // throw DivideByZeroError ();
        throw  std::runtime_error("ERROR: Divizion to zer0!\n");
    }
    return (float) num1 / num2; 
}

float quotient2(int num1, int num2)
{
 if (num2==0)
 {
      throw DivideByZeroError ();
 }
 return (float) num1 / num2;
 
}

int main(int argc, char *argv[], char *envp[]) 
{
	int RValue = false;
	int CaptureModeHex = 0;
	int NewChar=0;
	int nResult = 0;
    int arraySize = 2000;

    printf ("main - start\n");
    
    const char* ClassFileNaMe = "allegro.log";	
    // signal(SIGSEGV, posix_death_signal);
    
    // printHex(ClassFileNaMe);
    // segfault();    
    // fault_simple();
    
    /*
    __try
    {
         fault_simple();
        //fall();
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        memento();
    }    
    */
    
    int num1, num2;    
    cout << "BBeguTe 2 4ucLa gLq geLeHuq:\n";
    cin >> num1 >> num2;
    
    int i = 1;
    int j = i++;    
    cout << "Result j=i++:" << j << "\n";
    cout << "Result i++:" << i << "\n";
    
    i = 1;
    int k = ++i;
    cout << "Result ++i:" << k << "\n";

    // App *_app = new App();
    try
    {
        // _app->Run();
        // cout << "\n$ > Press Ctr-X to exit." << std::endl;
        float result =  quotient2(num1, num2);
        cout << "4acTHoe paBHo: " << result << endl; 
    }
    catch (std::runtime_error _str_error)
    {
        std::cout << _str_error.what();
        throw;
    }
    catch (DivideByZeroError err)
    {
        cout << "ERROR: ";
        err.printMesage();
        cout << endl;
        // return 1;
    }
    catch (...)
    {
        cout << "Unknown Error!!!!" << std::endl;
    }
    
//     return 0;
    
    //*************MAIN LOOP*****************//
    cout << "\n$ > Press Ctr-X to exit." << std::endl;

    do 
    {
        //This is simple Windows way:
        Sleep(55);
        // active_matrix->run_matrix();
       
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