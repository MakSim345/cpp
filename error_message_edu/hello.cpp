#include "gen.h"
#include "hello.h"

App::App()
{
    edu_num = 14;
    max_num = 1000;
    std::cout << "Run example number: " << edu_num << "\n";
}

int App::Run()
{
    edu_14();
    return 0;
}

void App::edu_14()
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
      cout << "Attempt number: " << try_conter << "\n";
      cin >> j;
      if (n >j)
        {
        cout << "Mine is bigger.\n";
        }
      else
        {
         if (n < j)
            cout << "Mine is less.\n";
         else
           {
            cout << "You WIN! ";
            cout << try_conter << " attempts were used.\n";
            done = true;
           }
        }
    } while(!done);
}

App::~App()
{
    std::cout << "\n-------------END-------------\n";
}

