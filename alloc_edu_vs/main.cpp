//
#include "gen.h" 
#include "div_error.h"
#include "my_exceptions.h"
#include "printHex.h"
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <signal.h>

int memento() // handle Segfault
{
    MessageBoxA(NULL,"Memento Mori","Exception catched!",NULL);
    return 0;
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

void super_allocation()
{

    int num1, num2;
    const int blockCount = 1024;
    //const int blockSize = (blockCount * blockCount); // 1048576
    const int blockSize = 20133;        // 520133 

    char **buf;
        
    std::cout << blockSize <<  " - Press any key to start memory allocation\n";
    _getch();
    for (int i = 0; i < blockCount; i++)
    {

        buf = (char**)malloc(blockCount * sizeof(char));

        for (int i = 0; i < blockCount; i++)
        {
            buf[i] = (char*)malloc(blockSize * sizeof(char));
            std::cout << ".";
        }

        std::cout << "\nOK. Memory allocated. Start to release\n";
        
        for (int i = 0; i < blockCount; i++)
        {
            free (buf[i]);
            std::cout << "_";
        }
        free (buf);
    }
    
    std::cout << "\nOK. Memory released\n";
    std::cout << "Press any key.";
    _getch();   
}

void my_memory_allocator()
{
    int num1, num2;
    const int blockCount = 1024;
    const int blockSize = (1024 * 1024); // 1048576
    //const int blockSize = 520133;        // 520133 

    char **buf;
    
    std::cout << blockSize <<  " - Press any key to start memory allocation\n";
    _getch();

    buf = (char**)malloc(blockCount * sizeof(char));

    for (int i = 0; i < blockCount; ++i)
    {
        buf[i] = (char*)malloc(blockSize * sizeof(char));
        std::cout << ".";
    }

    std::cout << "\nOK. Memory allocated\n";
    std::cout << "Press any key to release memory\n";
    _getch();

    for (int i = 0; i < blockCount; ++i)
    {
        free (buf[i]);
        std::cout << "_";
    }

    free (buf);
    std::cout << "\nOK. Memory released\n";
    std::cout << "Press any key.";
    _getch();
}

int main(int argc, char *argv[], char *envp[]) 
{
    int RValue = false;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;
    int arraySize = 2000;

    printf ("main - start\n");
    
#define YS_23443_A
#ifdef YS_23443_A    
    __try
    {
        // my_memory_allocator();
        super_allocation();

    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        // memento();
    }    
#endif

    //cout << "BBeguTe 2 4ucLa gLq geLeHuq:\n";
    //cin >> num1 >> num2;
#ifdef YS_23443_B
    // App *_app = new App();
    try
    {
        // my_memory_allocator();
        // _app->Run();
        // cout << "\n$ > Press Ctr-X to exit." << std::endl;
        //float result =  quotient2(num1, num2);
        //cout << "4acTHoe paBHo: " << result << endl; 
    }
    catch (std::runtime_error _str_error)
    {
        std::cout << _str_error.what();
        throw;
    }    
    catch (...)
    {
        cout << "Unknown Error!!!!" << std::endl;
    }
#endif    
	
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
        } 

	} while (!RValue);

	printf ("Application complete.\n");
	return 0;
}
