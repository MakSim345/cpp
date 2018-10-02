#include "gen.h"
#include "BankAccountFacade.h"
#include <Windows.h>

class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make FACADE\n";        
        testBankAccount();
        return 0;
    }

    void testBankAccount()
    {
        BankAccountFacade accessingBank = BankAccountFacade(12345678, 1234);

        accessingBank.withdrawCash(50.00);
        accessingBank.withdrawCash(900.00);
        accessingBank.depositCash(50.00);

        //facadeBank *myAuto = new facadeBank();
        //myAuto->turn_ignition_key();
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
