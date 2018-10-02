#include "gen.h"
#include "print_util.h"

using namespace std;

class vectorTestClass
{
public:
    void printVector()
    {
        for (int i = 0; i < intVector.size(); ++i)
        {
            cout << "intVector[" << i << "] = " << intVector[i] << "." << endl;    
        }
    }
    
    void createVector(int sizeP, int fillP)
    {     
        intVector = vector <int>(sizeP, fillP);
    }
    
    void addToVector(int toAddP)
    {
        intVector.push_back(toAddP);
    }

    int sumVector()
    {
        int retVal = std::accumulate (intVector.begin(), intVector.end(), 0);
        return retVal;
    }

private:
    vector <int> intVector;
};


float piCalculationRoutine(int iterationsP)
{
    float returnValuePi = 0;
    float z = 1;
    // for  (int i = 1; i< 100000000; i+=2)
    for  (int i = 1; i< iterationsP; i+=2)
        {
            returnValuePi = returnValuePi + (z*4 / i);
            cout << "returnValuePi = " << returnValuePi << "\n";
            z = z * (-1);
        }
    return returnValuePi;
}

void countPI()
{
    int places = 0;
    int iter = 0;
    // std::cout << array << std::endl; 
    std::cout << "Enter iterations " << endl;
    std::cin >> iter;
    std::cout << "and precision" << endl;
    std::cin >> places;
    // vector <int> int_arr (23, 10);
    std::cout.precision( places );

    long a1 = std::clock();
    std::cout << "Time Start: " << a1 << "\n";
    
    std::cout << "Pi = " << piCalculationRoutine(iter) << "\n";

    long b1 = std::clock();
    std::cout << "Time END: " << b1 << "\n\n";
    std::cout << "PI calculation took: " << (b1-a1)/1000.0 << " sec.\n";
}

int main()
{
    int array[5] = {1,2,3,4,5};
   
    //countPI();

    vectorTestClass *vectorContainer = new vectorTestClass();
    vectorContainer->createVector(5, -1);
    // mc->print_my_vector();
    for (int i = 0; i < 21; ++i)
        {
            // cout << "int_arr[" << i << "] = " << int_arr[i] << "." << endl;    
            vectorContainer->addToVector(i);
        }   
    
    // mc->print_my_vector();
    cout << "Sum (accumulate): " << vectorContainer->sumVector() << "\n";

    int a = 0;
    int b = 2048;
    int c = 1024;

    cout << a ? b : c;
    cout << "\n";
    cout << (a ? b : c);
    cout << "\n";
    // vector<my_class> my_class_array;  


    //*************MAIN LOOP*****************//
    cout << "\n$ > Press Any Key to exit." << std::endl;
    int RValue = false;
    int NewChar=0;
    do 
    {
        //This is simple Windows way:
        Sleep(55);
        // control of endless loop (may be also in monitor.cpp)    
        if (_kbhit())  // has anything been pressed from keyboard ?
        {
            NewChar=(unsigned char)_getch();
            RValue = true;            
        }     
    } while (!RValue);  
    printf ("Application complete.\n");
    return 0;
}

