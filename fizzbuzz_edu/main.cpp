#include "gen.h"
#include "utils.h"
#include "fizz_buzz.h"

void run_cube()
{
    // print_message();
    cout << "Enter cube dimention: " ;
    float side;
    cin >> side;
    cout << "Cube with side " << side << " is equal to " << cube(side) << endl;
}

int main()
{    
    //run_cube();
    
    std::auto_ptr <fizz_buzz> fzbz(new fizz_buzz());
    try
    {
        fzbz->Run();        
    }
    catch(std::runtime_error)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER\n";
    }

    return 1;
}

