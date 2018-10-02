#include "gen.h"
#include "figure.h"
// #include <Windows.h>

class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make some geometry\n";
        figure *_my_fig = new triangle();
        _my_fig->set_dim(23.0, 45.0);
        _my_fig->show_area();

        _my_fig = new circle();
        _my_fig->set_dim(23.0, 45.0);
        _my_fig->show_area();
        
        return 0;
    }

    ~App()
    {
        std::cout << "Good bye!\n";
    }
};

int main()
{
    //std::auto_ptr <CubeCalc> cube_calc(new CubeCalc());
    //cube_calc->run();
    App *geometry = new App();
    // std::auto_ptr <App> bakery(new App());
    
    try
    {
          geometry->Run();
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
    std::cout << "\nGood bye!\n";
    system("PAUSE");
    return 1;
}