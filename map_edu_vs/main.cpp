#include "gen.h"
#include "phone_book_map.h"
#include "person.h"
#include "fPrint.h"

#include <Windows.h>

class App
{
public:
    int Run()
    {
        phoneBook *myPhoneBook = new phoneBook();
        myPhoneBook->Run();
        return 0;
    }

    ~App()
    {
        std::cout << "\nGood bye!\n";
    }

};

int main()
{
    std::auto_ptr <App> my_maps(new App());
    try
    {
        my_maps->Run();
        //my_maps->create_big_file();
        //my_maps->search_by_name();
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
    std::string p;
    std::cout << "\nPress any key to exit...\n";
    cin >> p;
    return 1;
}
