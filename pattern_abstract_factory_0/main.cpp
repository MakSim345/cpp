#include "gen.h"
#include "cube_calc.h"
#include "map_tst.h"
#include "phone_book_map.h"
#include <Windows.h>

class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make some product...\n";
        //init_map();
        phone_book *pb = new phone_book();
        
        pb->read_data_file();
        pb->print_map();
        
        /*
         * long num_to_search = 345345325;
        std::cout << "search by number " << num_to_search << " - "<< search_by_number(num_to_search) << "\n";
        Number t;
        std::cout << "\nEnter new name:\n";
        cin >> t.name;
        
        std::cout << "Enter new number:\n";
        cin >> t.number;
        
        add_data_to_file(t.name, atol(t.number.c_str()));
        */
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
