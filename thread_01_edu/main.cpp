#include <stdio.h>
#include "math.h" // for sqrt function
#include "gen.h"
#include <atomic>
#include <cassert>
#include <thread>

class DivideByZeroError
{
 public:
    DivideByZeroError()
        : message("DivideByZeroError: Divide to ZERO!\n")
    {
        //
    }
    void printMesage() const { printf ("%s", message);}
 private:
     const char* message;
};

// A modulare sqare root foonction
double MySqrt(double dX)
{
    if (dX < 0.0)
    {
        throw -1;
        // throw "Can not take sqrt of negative number!"; // throw an exception of type "*char"
    }
    return sqrt(dX);
}

float quotient(int num1, int num2)
{
 if (num2==0)
 {
      throw DivideByZeroError ();
 }
 return (float) num1 / num2;

}

int test_catch_02()
{
    cout << "Enter a number: ";
    double dX;
    cin >> dX;
    try // look for an exception
    {
        cout << "The sqrt of " << dX << " is " << MySqrt(dX) << endl;
    }
    catch (char* strException)
    {
        cerr << "Error (user-defined message): " << strException << endl;
    }
    catch (int nNum)
    {
        cerr << "Error (unknown): " << nNum << endl;
    }
    return 0;
}

int test_catch_01()
{
    int num1, num2;

    cout << "Enter 2 numbers for division:";
    cin >> num1 >> num2;
    try
    {
     float result =  quotient(num1, num2);
     cout << "Result: " << result << endl;
    }
    catch (DivideByZeroError err)
    {
      cout << "ERROR: ";
      err.printMesage();
      cout << endl;
      return 1;
    }
}

int main( int argc, char *argv[] )
{
    return test_catch_01();
    // return test_catch_02();
}
