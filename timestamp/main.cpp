#include <iostream>
#include "utils.h"
#include "gen.h"
#include "timestamp.h"

inline float cube (const float s) {return s*s*s;}

using namespace std;


class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make timestamp...\n";
        
        tst = new timestamp();
        
        return 0;
    }

    ~App()
    {
        std::cout << "Good bye!\n";
    }

private:
    timestamp* tst;
};


int main()
{
    //std::auto_ptr <CubeCalc> cube_calc(new CubeCalc());
    //cube_calc->run();
    std::auto_ptr <App> my_timestamp(new App());
    try
    {
        my_timestamp->Run();
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
    system ("PAUSE");
    return 1;
}

