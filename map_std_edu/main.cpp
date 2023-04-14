#include "gen.h"
#include "password_generator.h"
#include "RandomNumbers.h"
#include "cube_calc.h"
#include "map_tst.h"
#include "phone_book_map.h"

class App
{
public:
    void create_big_file()
    {
        phone_book *pb = new phone_book("big_file.txt");
        CRandomNumbers *my_rnd = new CRandomNumbers();
        PassGenerator *my_name = new PassGenerator();
        
        long a = std::clock();
        std::cout << "Time Start: " << a << "\n";

        for (int i = 0; i < 1000000; i++)
        {
            long _number = my_rnd->getRandomNumber(100, 10000000);
            int _lenght_name =  my_rnd->getRandomNumber(3, 7);
            std::string _name = my_name->genPass(_lenght_name);

            pb->add_data_to_file(_name, _number);
        }
        
        long b = std::clock();
        std::cout << "Time END: " << b << "\n\n";
        std::cout << "Time TOTAL: " << (b-a)/1000.0 << " sec.\n";
    }

    void search_by_name()
    {
     phone_book *pb = new phone_book("big_file.txt");

     long a1 = std::clock();
     std::cout << "Time Start: " << a1 << "\n";

     pb->read_data_file();

     long b1 = std::clock();
     std::cout << "Time END: " << b1 << "\n\n";
     std::cout << "Open file Time TOTAL: " << (b1-a1)/1000.0 << " sec.\n";

     //phone_book *pb = new phone_book("text.txt");
     while (true)
      {
        string name;
        cout << "Enter name (or :q)\n";
        cin >> name;
        if (name == ":q")
            break;
        long a = std::clock();
        std::cout << "Time Start: " << a << "\n";

        std::string _the_number = pb->search_by_name(name);
        std::cout << "number for name " << name << " is " << _the_number << "\n";
        /*
        for (int i = 0; i < telBook.size(); i++)
        {
            if (telBook[i].name == name)
            {
                cout << name << " - " << telBook[i].number << "\n";
            }
        }
        */
        long b = std::clock();
        std::cout << "Time END: " << b << "\n\n";
        std::cout << "Time TOTAL: " << (b-a)/1000.0 << " sec.\n";
     }
    }

    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make some product...\n";
        //init_map();
        phone_book *pb = new phone_book();
        
        pb->read_data_file();
        pb->print_map();
                
        long num_to_search = 345345325;
        std::cout << "search by number " << num_to_search << " - "<< pb->search_by_number(num_to_search) << "\n";
        
        std::string name_to_search = "MAK";
        std::cout << "search by name " << name_to_search << " - "<< pb->search_by_name(name_to_search) << "\n";

        Number t;
        std::cout << "\nEnter new name:\n";
        cin >> t.name;

        std::string quit(":q");
        bool if_compare = t.name.compare(0, quit.length(), quit);
        
        if (!if_compare)
            return 0;

        std::cout << "Enter new number:\n";
        cin >> t.number;
        
        pb->add_data_to_file(t.name, atol(t.number.c_str()));
        
        return 0;
    }

    ~App()
    {
        std::cout << "\nGood bye!\n";
    }

};

int main()
{
    std::unique_ptr <App> my_maps(new App());    
    try
    {
        // my_maps->Run();
        my_maps->create_big_file();
        my_maps->search_by_name();
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
