#include "gen.h"
#include "hello.h"
#include "error_message.h"

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
