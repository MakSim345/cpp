//
#include "gen.h" 
#include "virtual_foo.h"
#include "my_smart_pointer.h"
#include "my_templates.h"
#include "video_buffer.h"

#define _CRTDBG_MAP_ALLOC

int game()
{
    int _size = 1640 * 1480;
    int *myPixels = new int[_size];
    
    // this->myPixels = new int[_size];

    for (int i = 0; i<_size; i++)
    {
        int a = rand() % _size;
        myPixels[i] = a;        
    }
    
    // simulate exception:
    if (_size > 0)
        return 1;

    delete [] myPixels;

    return 0;
}

void memory_leack_test()
{
    const int reserv = 2000;
    char* _my_str_old = new char[reserv];
    std::vector <char> _my_str(reserv, 121);
    // str.assign(reserv);
    strcpy(&_my_str[0], "memory leak");
    strcpy(&_my_str_old[0], "memory leak");
    
    for( int i = 0; i < _my_str.size(); i++ ) 
    {
        cout << _my_str[i] << " ";
    }
    cout << endl;
}

#define ZP_COUNT 10

// pointer to function:
template <class SuperType>
void Run(SuperType* functor)
{
    functor();
}

int main(int argc, char *argv[], char *envp[]) 
{
	int RValue = false;
	int CaptureModeHex = 0;
	int NewChar=0;
	int nResult = 0;
    int arraySize = 2000;

    srand(time(NULL));

    printf ("main - start\n");
    //CFucntInt *_my_int = new CFucntInt(arraySize);

    //Run(memory_leack_test);
    //memory_leack_test();

    Funct<int> cI(25);
	Funct<double> cD(3.12);
	cout << "cI " << cI.GetValue() << endl;
	cout << "cD " << cD.GetValue() << endl;
    cout << "cI " << endl;

    video_buffer screen;
    screen.makeFrame();
    
    //int a = game();

    int *p;
    int i = 10;

    p = &i;
    cout << "Address of i: " << p << "\n";
    cout << "Value of i: " << *p << "\n";


    //my_smart_pointer<video_buffer> pMyVideoBuffer (new video_buffer());    
    //pMyVideoBuffer->makeFrame();
    
    _CrtDumpMemoryLeaks();

//*************MAIN LOOP*****************//
cout << "\n$ > Press Any Key to exit." << std::endl;
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


