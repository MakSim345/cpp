#include "gen.h"
#include "ToDo.h"


using namespace std;

inline float cube(const float s) {return s*s*s;}

int test_foo()
{
    std::cout << "test_foo() function called!\n";
    return 1;
}


class App
{
public:
    int run()
    {
        std::cout << "Hello cruel world!\n";
        return 0;
    }
    ~App()
    {
        std::cout << "Good bye!\n";
    }

};


int main()
{
    std::unique_ptr <ToDo> main_object(new ToDo());
    // std::auto_ptr <ToDo> main_object(new ToDo());
    try
    {
        main_object->run();
    }
    catch(std::runtime_error)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER\n";
    }

    /*
    std::auto_ptr <App> bakery(new App());
    try
    {
        bakery->run();
    }
    catch(std::runtime_error)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER\n";
    }
    */
 
    return 1;
}
