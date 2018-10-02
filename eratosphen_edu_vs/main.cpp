//
#include "gen.h" 
#include "div_error.h"
#include "my_exceptions.h"
#include "printHex.h"
#include "eratosphen.h"

using namespace std;

int main(int argc, char *argv[], char *envp[]) 
{
    int RValue = false;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;
    int arraySize = 2000;

    // printf ("main - start\n");
    
    // system("PAUSE");

    // Eratosphen *_app = new Eratosphen();
    Eratosphen_simple *_app = new Eratosphen_simple();
    try
    {
        _app->inputInfo();
        long a = std::clock();
        std::cout << "Time Start: " << a << "\n";
        _app->Run();          
        long b = std::clock();
        std::cout << "Time END: " << b << "\n\n";
        std::cout << "Time TOTAL: " << (b-a)/1000.0 << " sec.\n";
        
        // cout << "\n$ > Press Ctr-X to exit." << std::endl;
        
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

        //nResult = produceRND();   
        //printf ("1-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);
   
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
