//main.cpp
#include "gen.h"
#include "AbstractFactory.h" 
#include "CarFactory.h"
#include <iostream>  

using namespace std; 

int main(int argc, char *argv[], char *envp[]) 
{
	int RValue = false;
	int CaptureModeHex = 0;
	int NewChar=0;
	int nResult = 0;
    int arraySize = 2000;

    printf ("main - start\n");
    
    const char* ClassFileNaMe = "allegro.log";	
    
    
    AbstractFactory* cf1 = new ConcreteFactory1(); 
    cf1->CreateProductA (); 
    cf1->CreateProductB (); 

    AbstractFactory* cf2 = new ConcreteFactory2(); 
    cf2->CreateProductA (); 
    cf2->CreateProductB (); 

    ToyotaFactory   toyotaFactory;
    FordFactory     fordFactory;

    use (&toyotaFactory);
    use (&fordFactory);


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