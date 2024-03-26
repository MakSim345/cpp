#include "gen.h"
#include "bread.h"
#include "error_message.h"

enum BakeryProductType
{
    iBread,
    MeatPasty,
    CabbagePasty,
    Cake
};

class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make some product...\n";
        // create gas and electric ovens:
        gasOven gas_oven = gasOven();
        electricOven elect_oven = electricOven();

        // create bread Factory:
        BreadMaker breadmaker = BreadMaker();

        // make the product:
        Bread *_my_bread = breadmaker.doBakeBread(gas_oven);

        return 0;
    }

    ~App()
    {
        std::cout << "App: Good bye!\n";
    }
};


int main()
{
    // std::auto_ptr <App> bakery(new App());
    std::unique_ptr <App> bakery(new App());
    try
    {
        bakery->Run();
    }

    catch (error_message err)
    {
        std::cout << "ERROR: ";
        err.printMessage();
        std::cout << "\n";
    }
    /*
    catch (std::runtime_error)
    {
        std::cout << "ATTN! Exception handler alarm!\n";
    }
    */
    system ("PAUSE");
    return 1;
}
