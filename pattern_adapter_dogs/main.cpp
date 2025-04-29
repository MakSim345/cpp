#include "gen.h"
#include "cat_adapter.h"
#include "cat.h"
#include "dog.h"

// Client function
void makeDogBark(const Dog& dogP)
{
    dogP.Bark();
}

class MainApp
{
public:
    int Run()
    {
        std::cout << "App: Started!\n";

        Cat myCat;

        CatAdapter adaptedCat(myCat);

        makeDogBark(adaptedCat);

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
    std::unique_ptr <MainApp> _my_dogs(new MainApp());
    _my_dogs->Run();

    /*
    catch (std::runtime_error)
    {
        std::cout << "ATTN! Exception handler alarm!\n";
    }
    */
    // system ("PAUSE");
    return 1;
}
