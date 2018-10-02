#include "gen.h"
#include "cube_calc.h"
#include "trace_logger.h"
#include "trace.h"

using namespace std;

inline float cube(const float s) {return s*s*s;}

class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make some product...\n";        
        return 0;
    }
    
    App()
    {
        
    }

    ~App()
    {
        std::cout << "Good bye!\n";
    }

    void test_foo()
    {
        LOG_TRACE;
        level_one();        
    }

    int level_one()
    {
        LOG_TRACE;
        level_two();
        int i = 0;
        i++;
        return i;
    }
    
    int level_two()
    {
        LOG_TRACE;
        int i = 0;
        i++;
        return i;
    }

private:
    
};

int test_foo()
{
    // LOG_TRACE;
    int i = 0;
    i++;
    return i;
}

int main()
{
    // CubeCalc *cube_calc = new CubeCalc();
    //std::auto_ptr <CubeCalc> cube_calc(new CubeCalc());
    //cube_calc->run();
    
    //std::auto_ptr <App> bakery(new App());
    //bakery->Run();
    // test_foo();
    App _myapp;
    _myapp.test_foo();

    return 1;
}
