//
#include "gen.h" 
#include <time.h> 
#include "singleton.h"
#include "virtual_foo.h"

int main(int argc, char *argv[], char *envp[]) 
{
	int RValue = false;
	int CaptureModeHex = 0;
	int NewChar=0;
	int nResult = 0;
    // GetTime();
    // CTime t;
    printf ("main - start\n");
    
    //std::vector < boost::shared_ptr<myABC> > BunchOfObjects;
    //BunchOfObjects.push_back(boost::shared_ptr<A>(new B));

    // test Singleton - incorrect way:
    // Singleton bad_singleton;

    // correct way:
    // no instances, get it from class.
    Singleton &singleton1 = Singleton::getSingletonInstance();
    singleton1.dataM = 20;

    std::cout << "singleton1.dataM = " << singleton1.dataM << std::endl;

    Singleton& singleton2 = Singleton::getSingletonInstance();
    std::cout << "singleton2.dataM = " << singleton2.dataM << std::endl;
    // Note that singleton2.dataM is also equal to 20!
    // so, singleton1 == singleton2

    // Directly change dataM to 50 and check it is still one singleton:
    Singleton::getSingletonInstance().dataM = 50;

    std::cout << "singleton1.dataM = " << singleton1.dataM << std::endl;
    std::cout << "singleton2.dataM = " << singleton2.dataM << std::endl;
    std::cout << "Direct:    dataM = " << Singleton::getSingletonInstance().dataM << std::endl;

    /* 
    * Test the Copy Constructor.
    * Note: comment out "Singleton(Singleton const&) = delete;"
    * to see the difference.
    * 
    Singleton singletonN = singleton1;
    singletonN.dataM = 100;
    std::cout << "singleton1.dataM = " << singleton1.dataM << std::endl;
    std::cout << "singletonN.dataM = " << singletonN.dataM << std::endl;
    */

    Logger::getLoggerInstance()->openLogFile("my_new_file.txt");    
    Logger::getLoggerInstance()->writeLogFile("START:\n");

    Logger *l = Logger::getLoggerInstance();
    l->writeLogFile("Ax-Xa");
    // Logger::Instance()->closeLogFile();
    float a = 12.5;
    float speed_fast = 20.0;
    float b = 6.25;
    float speed_slow = 40.0;
    
    map<float, float> WaveForms;
    
    WaveForms[a] = speed_fast;
    WaveForms[b] = speed_slow;

    
    printf ("result = %.2f\n", WaveForms[a]);
    system ("PAUSE");
    return 0;
    
    //*************MAIN LOOP*****************//
    cout << "\n$ > Press Any KEY to EXIT!" << std::endl;
    do 
    {
        //This is simple Windows way:
        Sleep(55);
        // Logger::Instance()->writeLogFile(produceRND());
        // active_matrix->run_matrix();
        printf (".");
        // nResult = produceRND(); 
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


