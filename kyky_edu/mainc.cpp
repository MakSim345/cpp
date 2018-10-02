#include "gen.h"
#include "pass.h"
#include "kyky.h"

class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make fun...\n";
        return 0;
    }
    ~App()
    {
        std::cout << "Good bye!\n";
    }

};


int main(int argc, char *argv[], char *envp[]) 
{

    printf ("main - start\n");   

    
    std::auto_ptr <Pass> pass_calc(new Pass());
    std::cout << "---------------------------\n";
    std::cout << pass_calc->run(10) << "\n";
    std::cout << "---------------------------\n";
    
    
    kuku(2);
    // printf ("Application complete.\n");
    return 0;
}

