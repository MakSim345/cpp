#include "gen.h"
#include "Subscription.h"
#include "EventDispatcher.h"
#include <Windows.h>

void usleep(__int64 usec) 
{ 
    HANDLE timer; 
    LARGE_INTEGER ft; 

    ft.QuadPart = -(10*usec); // Convert to 100 nanosecond interval, negative value indicates relative time

    timer = CreateWaitableTimer(NULL, TRUE, NULL); 
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0); 
    WaitForSingleObject(timer, INFINITE); 
    CloseHandle(timer); 
}

class Foo : public EventDispatcher
{
public:
    void Run ( void )
    {
        for ( int key = 0 ; key < 5 ; key ++ )
        {
            this->DispatchEvent ( "FOO_EVENT_1" );
            this->DispatchEvent ( "FOO_EVENT_2" );
            // usleep ( 500000 );
            Sleep(500);
        };
    };
};

class Bar
{
public:
    void EventHandler1 ( void )
    {
        cout << "FOO_EVENT_1 occuredn";
    };

    void EventHandler2 ( void )
    {
        cout << "FOO_EVENT_2 occuredn";
    };
};


class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make Observer\n";

        Foo* foo = new Foo ( );
        Bar* bar = new Bar ( );

        foo->AddEventListener ( "FOO_EVENT_1" , bar , &Bar::EventHandler1 );
        foo->Run();
    
        foo->RemoveEventListener ( "FOO_EVENT_1" , bar , &Bar::EventHandler1 );
        foo->AddEventListener ( "FOO_EVENT_2" , bar , &Bar::EventHandler2 );
        foo->Run();

        return 0;
    }

    ~App()
    {
        std::cout << "\nGood bye!\n";
    }

};

int main()
{
    std::auto_ptr <App> my_facade(new App());

    try
    {
        my_facade->Run();
    }
    catch(std::runtime_error)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER\n";
    }
    /*
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER has number - " << EXCEPTION_EXECUTE_HANDLER << "\n";
    }    
    */
    system("PAUSE");
    return 1;
}
