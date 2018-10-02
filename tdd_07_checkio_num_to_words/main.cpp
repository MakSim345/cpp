#include "gen.h"
#include "parser.h"
#include "error_message.h"

class App
{

public:
    App()
    {
        edu_num = 42;
        max_num = 1000;
        std::cout << "Run : " << edu_num << "\n";
    }
    ~App()
    {
        std::cout << "\n-------------END-------------\n";
    }

    int Run()
    {
        std::cout << "\n------------- START -------------\n";        
        checkio _obj = checkio();
        std::string _ret_val = "two hundred twelve";
        std::cout << _ret_val << "\n";
        std::cout << *_ret_val.rbegin() << "\n";
        // char lastChar = *_ret_val.rbegin();
        return 1;
    }

    /*
     * cout << "viNumbers: " << viNumbers.empty() << "\n";
        
        viNumbers = _obj.run(viNum); // checkio();
        
        for (int _num = 0; _num < viNumbers.size(); _num++)
        {
            std::cout << "Result: " << viNumbers[_num] << "\n";
        }
        return 0;
     * int* checkio()
    {
        int _my_array [10] = {1,2,3,4,5,6,7,8,9};
        std::cout << "_my_array: " << _my_array << std::endl; 
        return _my_array;
    }
        for (int _num = 0; _num <= 9; _num++)
        {
            std::cout << "array element " << _num << "\n";
        }
    */

private:
    int edu_num;
    int max_num;
};

int main()
{
    //std::auto_ptr <App> fact_calc(new App());
    //fact_calc->run();
    std::auto_ptr <App> app(new App());
    try
    {
        app->Run();
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
    return 1;
}
