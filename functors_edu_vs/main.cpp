#include "gen.h"
#include "utils.h"
#include "memory"
#include <vector>
#include <algorithm>

void testESP()
{
    COPSvCommunication *tRun = new COPSvCommunication();

    printf ("string - %s\n", tRun->getModuleVersionString() );

    const char* snIndex = strstr(tRun->getModuleVersionString(), "Pr. 8");

    //if (strstr(tRun->getModuleVersionString(), "Pr. 8") == 0)
    if (snIndex)
    {
        printf ("Compare - MATCH, OK\n");
    }
    else
    {
        printf ("Compare - NOT MATCH\n");
    }
}

void testProgrammers()
{
    // long g_lTimeTick = 0;
    const int ARR_SIZE = 9;
    Programmers *prog [ARR_SIZE];
    Programmers *ptr = nullptr;

    for (int i=0; i < ARR_SIZE; i++)
    {
        ptr = new Programmers(i + 100, i);
        prog[i] = ptr;
    }

    int w, a;
    int count = ARR_SIZE;

    //create pointer to pointer,
    //array's name ("prog") is a pointer to it's first element
    Programmers **iter = prog;

    for (int i=0; i < count; i++)
    {
        ptr = *iter++;
        ptr->getParams(w, a);
        if( *(iter-1) != nullptr )
        {
            delete *(iter-1);
            ptr = nullptr;
        }
        cout << w << "\t" << a << endl;
    }
}

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
        return argP<<1; // argP *= 2;
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
    auto function = testProgrammers;

    // function();
    // DoSomethingFunctor my_functor(7);
    // std::cout << "Functor 23: " << my_functor(23) << std::endl;

    // lambda:
    int xl = 1;
    auto l1 = []{cout << "Hello from Lambda 1." << endl;};
    auto l2 = [](int n){cout << "Hello from Lambda 2: " << n << endl;};
    auto l3 = [xl](int n){cout << "Hello from Lambda 3: " << n+xl << endl;};
    auto l4 = [&xl](int n){xl=55; cout << "Hello from Lambda 4: " << n+xl << endl;};
    l1();
    l2(0x1234567u);
    l3(12);
    l4(50);

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


    int x = 2;
    vector <int> vec;
    vec.assign(5, 0);
    // std::multiplies

    vec[0] = 1; vec[1] = 5; vec[2] = 4; vec[3] = 2;vec[4] = 3;

    cout << "Capacity vector =" << vec.capacity() << endl;
    cout << "Size vector =" << vec.size() << endl;

    // ForEach(vec, [](int value) {std::cout << "Value: " << value << endl;});
    
    ForEach(vec, PrintValue);
    
    for_each(vec.begin(), vec.end(), AddValue(x));
    
    AddValue my_functor = AddValue(x);
    my_functor.mVal;

    vector<float> v;
    cout << "Capacity vector =" << v.capacity() << endl;
    cout << "Size vector =" << v.size() << endl;
    v.assign( 5, 10 );

    v[2] = 16.4;
    v[3] = 20.6;
    v.push_back(17.8);
    v.push_back(-7.3);
    sort(begin(v), end(v));

    // vector <Dog> v(Dog(3), Dog(1));
    // v[0] = Dog(3);
     system ("PAUSE"); // wait for press any key in VS mode

    return 0;

}



