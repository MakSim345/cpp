#include "gen.h"
#include "plane.h"
#include "error_message.h"

class App
{

public:
    App()
    {
        edu_num = 14;
        max_num = 1000;
        std::cout << "Run : " << edu_num << "\n";
    }
    ~App()
    {
        std::cout << "\n-------------END-------------\n";
    }


    int Run()
    {
        // edu_14();
        CropperPlane plane;
        return 0;
    }

    void edu_14()
    {
        int n = 0;
        int j = 0;
        int try_conter = 0;
        bool done = false;
        srand(time(0));
        n = rand() % max_num;
        std::cout << "I have a number up to " << max_num;
        std::cout << ". Guess what is it?\n";
        do
        {
        try_conter ++;
        std::cout << "Attempt number: " << try_conter << "\n";
        std::cin >> j;
        if (n >j)
            {
            std::cout << "Mine is bigger.\n";
            }
        else
            {
            if (n < j)
                std::cout << "Mine is less.\n";
            else
            {
                std::cout << "You WIN! ";
                std::cout << try_conter << " attempts were used.\n";
                done = true;
            }
            }
        } while(!done);
    }

private:
    int edu_num;
    int max_num;
};

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
