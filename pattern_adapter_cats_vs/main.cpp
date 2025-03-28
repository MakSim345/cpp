#include "gen.h"
#include "cat_if.h"
#include "cats.h"
#include "tiger.h"
#include "home_cat_adapter.h"
#include "cat_info_printer.h"


class MainApp
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make some product...\n";

        iHomeCat* vaska = new StreetCat();
        vaska->setName("Bacbka");

        iHomeCat* wagner = new PedigreedCat();
        wagner->setName("Wagner");

        iWildCat* my_tiger = new Tiger();

        CatInfoPrinter* cip = new CatInfoPrinter();
        cip->PrintCatInfo(*vaska);
        cip->PrintCatInfo(*wagner);

        HomeCatAdapter *hca = new HomeCatAdapter(*my_tiger);

        // cip->PrintCatInfo(*my_tiger); // error, wrong parameter type!!
        cip->PrintCatInfo(*hca);

        /*
        std::cout << "New cat name: " << vaska->Name() << "\n";
        std::cout << "    -info : ";
        vaska->Meow();
        std::cout << "    -info : ";
        vaska->Scratch();


        std::cout << "New cat name: " << vagner->Name() << "\n";
        std::cout << "    -info : ";
        vagner->Meow();
        std::cout << "    -info : ";
        vagner->Scratch();
        */

        return 0;
    }

    ~MainApp()
    {
        std::cout << "App: Good bye!\n";
    }

};


int main()
{
    // std::auto_ptr <MainApp> _my_cats(new MainApp());
    std::unique_ptr <MainApp> _my_cats(new MainApp());
    _my_cats->Run();

    /*
    catch (std::runtime_error)
    {
        std::cout << "ATTN! Exception handler alarm!\n";
    }
    */
    // system ("PAUSE");
    return 1;
}
