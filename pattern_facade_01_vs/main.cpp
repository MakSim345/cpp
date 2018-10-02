#include "gen.h"
#include "facade.h"
#include "facadeFileTransfer.h"
#include "facadeAuto.h"
#include <Windows.h>

class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make FACADE\n";        
        runFacadeAuto();
        return 0;
    }

    void runFacadeAuto()
    {
        facadeAuto *myAuto = new facadeAuto();
        myAuto->turn_ignition_key();
    }

    void runFacadeFileTransfer()
    {
        facadeFileTransfer _ft;
        _ft.sendFile("logFile.txt");
    }

    void facadeTemplate()
    {
        MyFacade _my_facade;
        _my_facade.run();
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
