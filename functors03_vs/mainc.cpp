#include "gen.h"
#include "utils.h"
#include "memory"
#include <vector>
#include <algorithm>

struct Dog
{
    Dog (int ageP)
        : m_age(ageP)
    {}

    int m_age;
};

struct DoSomethingFunctor
{
    DoSomethingFunctor (int x)
        : m_x (x)
    {}

    int operator () (int y) const
    {
        return m_x + y;
    }

    int m_x;
};

struct Eventfunctor
{
    Eventfunctor():
        evenSum(0),
        evenCount(0)
    { }

    void operator () (int valueP)
    {
        if (valueP %2 == 0)
        {
            evenSum += valueP;
            evenCount++;
        }
    }

    void ShowEventSum()
    {
        std::cout << "Sum even numbers:" <<  evenSum << std::endl;
    }

    void ShowEventCount()
    {
        std::cout << "Count even numbers:" <<  evenCount << std::endl;
    }

    int evenSum;
    int evenCount;
};


void PrintValue(int valueP)
{
    std::cout << "Value:" <<  valueP << std::endl;
}

struct Mult
{
    int operator()(int argP)
    {
        return argP << 1; // argP *= 2;
    }

};

class AddValue
{
public:
    int mVal;
    AddValue(int inputP):mVal(inputP) {}

    void operator () (int i)
    {
        cout << i + mVal << endl;
    }
};

void ForEach(const std::vector<int>& values, void (*p_funcP)(int))
{
    //for (int value ; values)
    //    p_funcP(value);
    for_each(values.begin(), values.end(), p_funcP);
}


template <typename T>
int sink (int arg [], int size, T op)
{
    int sum = 0;
    for (int i = 0; i<size; i++)
    {
        sum += op(arg[i]);
    }
    return sum;
}

int main(int argc, char *argv[], char *envp[])
{
    printf ("main - start\n");
    
    Eventfunctor ef;
    int arr[] = {1,2,55,99,44,3};
    const int arr_size = sizeof(arr)/sizeof(int);
    // for (auto element:arr)
    
    Mult mult_1;
    std::cout << sink(arr, arr_size, mult_1);

    for (int i = 0; i < arr_size; i++)
    {
        ef(arr[i]);
    }
    ef.ShowEventCount();
    ef.ShowEventSum();

    AddValue my_functor = AddValue(10);
    my_functor.mVal;
    /*
    vector<float> v;
    cout << "Capacity vector =" << v.capacity() << endl;
    cout << "Size vector =" << v.size() << endl;
    v.assign( 5, 10 );

    v[2] = 16.4;
    v[3] = 20.6;
    v.push_back(17.8);
    v.push_back(-7.3);
    sort(begin(v), end(v));
    */
    vector <Dog> v = {Dog(3), Dog(1)};
    // v[0] = Dog(3);
    system ("PAUSE"); // wait for press any key in VS mode

    return 0;

}
