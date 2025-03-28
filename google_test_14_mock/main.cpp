#include "gen.h"

class App
{
public:
    int Run()
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
    // std::auto_ptr <Person> pers(new Person());
    std::unique_ptr <App> app(new App());
    app.run();
    return 0;
}
