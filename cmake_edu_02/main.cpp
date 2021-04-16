#include "gen.h"
#include "error_message.h"
#include "utils.h"
#include "ChuckNorris.h"

using namespace std;

class App
{
public:
    int Run()
    {
        std::cout << "Let's get a random fact about Chuck Norris...\n";
        
		std::cout << std::endl;
        ChuckNorris chuckNorris;
        std::string fact = chuckNorris.getFact();
		std::cout << fact << std::endl;
		std::cout << std::endl;

        // make the product:
        // Bread *_my_bread = breadmaker.doBakeBread(gas_oven);
        // print_message();
    	int side;
    	int a = 34;
	    std::cout << "Enter cube dimention: " ;
    	std::cin >> side;
    	// cout << "Cube with side " << side << " is equal to " << cube(side) << endl;
    	printf("side = %d \n", side);
    	float res = a / side;
    	printf("result %d DIV %d = %d\n",a, side, res); 

        return 0;
    }

    ~App()
    {
        std::cout << "App: Good bye!\n";
    }

};

int main(int argc, char** argv)
{
    // std::auto_ptr <App> bakery(new App());
    std::unique_ptr <App> chkNor(new App());
    try
    {
        chkNor->Run();
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
    system ("PAUSE");    
    return 0;
}

