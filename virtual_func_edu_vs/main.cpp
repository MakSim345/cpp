#include "gen.h"
#include "figure.h"

class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make some geometry\n";
        Figure *myFigure = new Triangle();
        myFigure->setDimentions(23.0, 45.0);
        myFigure->showArea();

        myFigure = new Circle();
        myFigure->setDimentions(23.0, 45.0);
        myFigure->showArea();

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