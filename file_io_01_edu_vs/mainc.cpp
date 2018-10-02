#include "gen.h"
#include "worker.h"
#include "utils.h"
#include "cTimer.h"
#include "map_tst.h"
#include "vector_tst.h"
#include "RandomNumbers.h"
#include "template_tst.h"

#include "GenieUsabilityLogger.h"

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
    CTimer *_time = new CTimer ();
    
    std::cout << "Time Start: " << std::clock() << "\n";

    GenieUsabilityLogger *logger = new GenieUsabilityLogger();
    logger->OpenLogFile(std::string("log_file"));

    /*
    vector <int> viRandomNumbers;
    vector <int> mImageArray;

    cout << "viRandomNumbers: " << viRandomNumbers.empty() << "\n";
    viRandomNumbers.push_back(23);
    CRandomNumbers *rnd_arr = new CRandomNumbers();
     
    std::cout << "Time Start:" << std::clock() << "\n";
    viRandomNumbers = rnd_arr->getRandomNumbers(0, 1000, 100000, false);
    std::cout << "Time end:" << std::clock() << "\n";
    // vector_string();
    
    cout << "Result maximum(23.6, 45.7): " << maximum(23.6, 45.7) << "\n";
    cout << "Result       maximum(2, 5): " << maximum(2, 5) << "\n";
    
    std::cout << "Time Start:" << std::clock() << "\n";
    sort(viRandomNumbers.begin(), viRandomNumbers.end());
    std::cout << "Time END:" << std::clock() << "\n";
    */

    /*
    vector<int>::const_iterator _iterator;
    for(_iterator = viRandomNumbers.begin(); _iterator != viRandomNumbers.end(); ++_iterator) 
    {
        // std::cout << (*_iterator) << std::endl;
        std::cout << (*_iterator) << ", ";
    }
    */
    std::cout << std::endl;
    //ostringstream sStr;
    // map_test();

    int n_total = Add(23, 16);
    long l_total = Add<long>(10245, 35234);
    double d_total = Add<double>(12.60, 35.98); 

    //*************MAIN LOOP*****************//
 cout << "Press Ctr-X to exit." << std::endl;
 do 
  {
    //This is simple Windows way:
    Sleep(1000);
    
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


} while (!RValue);  

#ifdef FILE_OUTPUT
 if (1 == nOpenFileToken)
   fclose (fi);
#endif
 
printf ("Application complete.\n");
return 0;
}

