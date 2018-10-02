#include "gen.h"
#include "facade.h"
#include "facadeFileTransfer.h"

class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make facade File Transfer\n";
        
        //MyFacade _my_facade;
        //_my_facade.run();

        runFacadeFileTransfer();

        return 0;
    }

    void runFacadeFileTransfer()
    {
        facadeFileTransfer _ft;
        _ft.sendFile("logFile.txt");
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
    return 1;
}
