//
#include "gen.h" 
#include "virtual.h"
#include "matrix.h"

int memento() // handle Segfault
{
    MessageBoxA(NULL,"Memento Mori","Exception catched!",NULL);
    return 0;
}

void fall() // segfault generation
{
      // int *p = 0x00000000;   
      // p[0] = 13;
    const int _m_size = 25;
    int _m_array[_m_size];
    for (int i = 0; i<_m_size+2; i++)
    {
        //int a=rand() % my_array.size();
        _m_array[i] = rand() % _m_size;
        cout << i <<  " - " << _m_array[i];
        cout << "\n";
    }
    cout << endl;
}


int main(int argc, char *argv[], char *envp[]) 
{
	int RValue = false;
	int CaptureModeHex = 0;
	int NewChar=0;
	int nResult = 0;
    int arraySize = 2000;

    printf ("main - start\n");
    
    // printHex(ClassFileNaMe);
    baseClassA classA;
    derivedClassB classB;

    std::cout << "baseClassA value: " << classA.get() << std::endl;
    std::cout << "derivedClassB value: " << classB.get() << std::endl;

    derivedClassFoo *pDerivedFoo = new derivedClassFoo ();
    pDerivedFoo->Foo();

    classDerivedAbstract *my_class_A = new classDerivedAbstract();
    
    my_class_A->Abstr(); 
    my_class_A->fun(); 
    my_class_A->~classDerivedAbstract();

    matrix* screenSaver = new matrix();

    /*
    __try
    {
        fail();
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        memento();
    }
    */
    
//*************MAIN LOOP*****************//
cout << "\n$ > Press Ctr-X to exit." << std::endl;
do 
{
    //This is simple Windows way:
    Sleep(55);
    screenSaver->run_matrix();
    
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


