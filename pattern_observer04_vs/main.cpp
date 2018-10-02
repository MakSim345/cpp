#include "gen.h"

#include "Publisher.h"
#include "Observer.h"
#include "auto.h"
#include <Windows.h>

class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make Observer\n";
        
        Publisher subj;
        DivObserver divObs1(&subj, 4); // 7. Client configures the number and
        DivObserver divObs2(&subj, 3); //    type of Observers
        ModObserver modObs3(&subj, 3);
        subj.setVal(14);

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
