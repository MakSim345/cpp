#include "gen.h" 
#include "div_error.h"
#include "my_exceptions.h"
#include "printHex.h"


class Auto
{
private:
    string _auto_name;

public:
    static int gCounter;

    Auto()
        :_auto_name("noname-")
    {
        std::cout << "New Auto " << _auto_name << " created\n";
    }
   ~Auto() 
   {
       std::cout << _auto_name << ": deleted!\n";
   }
};


int memento() // handle Segfault
{
    MessageBoxA(NULL,"Memento Mori", "Exception catched!", NULL);
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

void fall_in_file()
{
  char * s = "short_text";
  sprintf(s,"This is very long text");
}

void fall_in_pointers()
{
    int * pointer = NULL;
    *pointer = 13;
}

void open_my_file()
{
    FILE *fp = fopen( "myfile.txt","r" );
    if ( !fp )
    {
        std::stringstream ss;
        ss <<"Error opening file, error #"<< errno <<" translates to " << strerror(errno);
        throw std::runtime_error( ss.str() );
    };
}

void func( int x )
{
    char* pleak = new char[1024]; // might be lost => memory leak
    std::string s_string( "hello world" ); // will be properly destructed

    if ( x ) throw std::runtime_error( "boom" );

    delete [] pleak; // will only get here if x == 0. if x!=0, throw exception
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
        
    throw_error t_err;
    //Exp _exp;
    // _exp.run();
    /*
    try
    {
        // func( 10 );
        fall_in_file();
    }
    catch ( const std::exception& msg )
    // catch ( const char* msg)
    {
        std::cout << "Application had exception handling with message: ";
        // std::cout << msg;
        printf ("%s\n", msg.what());
        std::cout << "-------------------" << strerror(errno);
        //return 1;
    }
    catch (...)
    {
        cout << "Unknown Error!!!!" << std::endl;
        std::cout << "-------------------" << strerror(errno);
        
    }*/

    
    //std::stringstream ss;
    std::auto_ptr <Auto> bakery(new Auto());
    char* pleak = new char[1024]; // might be lost => memory leak
    __try
    {
        //fault_simple();
        //fall();
        //t_err.Run();
        // open_my_file();
        
        // fall_in_file(); // call an exception        
        delete [] pleak; // will only get here if x == 0. if x!=0, throw exception
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        std::cout << "-------------------" << strerror(errno);        
        // memento();
    } 
    /* */
    
#ifdef YS_TEST213413_B    
    
    try
    {
        //my_exceptions m_ex;
        //m_ex.run();
        //fault_simple();
        // t_err->Run();
        // open_my_file();
        
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
        return 1;
    }
    catch (...)
    {
        cout << "Unknown Error!!!!" << std::endl;
    }
#endif    
    //*************MAIN LOOP*****************//
    cout << "\n$ > Press any key to exit." << std::endl;

    do 
    {
        //This is simple Windows way:
        Sleep(55);
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
    
        _CrtDumpMemoryLeaks();
        return 0;
}
