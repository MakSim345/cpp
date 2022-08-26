/* Computes and prints n! for a given n.
   Uses several basic elements of C++.
*/

// #include <stdio>
#include <thread>
#include <atomic>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

static std::atomic<int> av;
static int gv;

using String = std::string;

class Entity
{
public:
    Entity() : sNameM("Unknown") {};
    Entity(const String& nameP) : sNameM(nameP) {};

    // ~Entity();
    const String& GetName() const { return sNameM; }

private:
    String sNameM;
};

void hello()
{
    std::cout <<  "Hello world, I'm a thread!" << std::endl;
}

static void counterIncrement()
{
    for (auto i = 0; i < 1000; i++)
    {
        // Atomic increment
        ++av;

        // unsafe code alert
        ++gv;
        // cout << std::this_thread.get_id();
        cout << "thread: av=" << av << " gv=" << gv << endl;
    }
}


void calculate_factorial()
{
    // Declarations of variables
    int factArg = 0;
    long fact(1.0);
    do
    {
        cout << "Factorial of: ";
        cin >> factArg;
        if (factArg < 0)
        {
            cout << "No negative values, please!" << endl;
        }
    } while (factArg < 0);
    int i = 2;
    while (i <= factArg)
    {
        fact = fact * i;
        i = i + 1;
    }
    cout << "The Factorial of " << factArg << " is: " << fact << endl;
}

int test_hello_thread()
{
  std::thread thrd(&hello);
  thrd.join();
  return 0;
}

int GetRandom(int maxP)
{
    static bool isFirstTime = true;
    if (isFirstTime)
    {
        srand(time(NULL));
        isFirstTime = false;
    }
    auto retVal = rand() % maxP;
    return retVal;
}

int main()
{
    std::thread ta(counterIncrement);
    std::thread tb(counterIncrement);
    ta.join();
    tb.join();
    
    // assert(static_cast<int>(av) != gv);
    // cout << "av=" << av << " gv=" << gv << endl;

    std::string name0 = "Cherno"s + "hello";
    /*
    for (int i = 0; i < 10000; i++)
    {
        cout << "RND=" << GetRandom(100) << "  ";
    }
    cout << endl;
    */
    Entity* e;
    {
        Entity* entity = new Entity("Cherno");
        e = entity;
        std::cout << entity->GetName() << std::endl;
    }
    
    system("PAUSE");
    return 0;
}
