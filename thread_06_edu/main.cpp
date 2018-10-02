/* Computes and prints n! for a given n. 
   Uses several basic elements of C++. */

#include "gen.h"

using namespace std;

static std::atomic<int> av;
static int gv;

void hello()
{
  std::cout <<
    "Hello world, I'm a thread!"
    << std::endl;
}
 
static void entry()
{
    for (auto i = 0; i<1000; i++)
    {
        // Atomic increment
        ++av;
        
        // unsafe code alert
        ++gv;

     // cout << "thread: av=" << av << " gv=" << gv << endl;
    }
}


void calculate_factorial()
{
// Declarations of variables
    int factArg = 0 ;         
    long fact(1.0) ;            
    do 
    {
        cout << "Factorial of: "; 
        cin >> factArg;      
        if ( factArg < 0 )
        {
            cout << "No negative values, please!" << endl;
        } 
    }
    while (factArg < 0) ; 
    int i = 2;
    while ( i <= factArg ) 
    {   
        fact = fact * i; 
        i = i + 1;
    } 
    cout << "The Factorial of " << factArg << " is: " << fact << endl;
}
/*
int main(int argc, char* argv[])
{
  boost::thread thrd(&hello);
  thrd.join();
  return 0;
}
*/

int main() 
{ 
    std::thread ta(entry);
    std::thread tb(entry);
    ta.join();
    tb.join();
    // assert(static_cast<int>(av) != gv);
    cout << "av=" << av << " gv=" << gv << endl;

    return 0; 
}
