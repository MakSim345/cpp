#include "gen.h"
#include "washing_machine.h"


#include <Windows.h>

class App
{
public:
    int Run()
    {
        std::cout << "----------- make FACADE pesu kone\n";

        runFacadeWashingMachine();

        return 0;
    }

    void runFacadeWashingMachine()
    {
        // Facade Sample:
        WashingMashine *wm = new WashingMashine();
        wm->wash_cotton();
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

    bool RValue = false;

    cout << "Press anykey to exit." << std::endl;
    do
    {
        //This is simple Windows way:
        Sleep(1000);

        // control of endless loop (may be also in monitor.cpp)
        if (_kbhit())  // has anything been pressed from keyboard ?
        {
            RValue = true;
        }

    } while (!RValue);


    cout << "Application completed." << std::endl;
    return 1;
}
