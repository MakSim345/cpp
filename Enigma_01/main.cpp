
#include "gen.h" 
//#include <time.h> 
//#include "singleton.h"
//#include "virtual_foo.h"

typedef struct enigma_t {
    uint64_t counter;
    uint8_t  sizeRotor;
    uint8_t  numRotors;
    uint8_t  *reflector;
    uint8_t **rotors;
};

int main(int argc, char *argv[], char *envp[]) 
{
	int RValue = false;
	int CaptureModeHex = 0;
	int NewChar=0;
	int nResult = 0;
  
    printf ("main - start\n");
    
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