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

namespace MyMSF
{
class Entity
{
public:
    Entity()
    {
        std::cout << "Created Entity!" << std::endl;
    }

    ~Entity()
    {
        std::cout << "Destroyed Entity!" << std::endl;
    }

    void Print()
    {
        std::cout << "Print Entity!" << std::endl;
    }
};
} // end MyMSF namespace

void PrintValue(int valueP)
{
    std::cout << "Value:" <<  valueP << std::endl;
}

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


int main(int argc, char *argv[], char *envp[])
{
    printf ("main - start\n");
    auto function = testProgrammers;
    
    function();

    {
        std::unique_ptr<MyMSF::Entity> my_Entity(new MyMSF::Entity);
        my_Entity->Print();
    }
    
    // DoSomethingFunctor my_functor(7);
    // std::cout << "Functor 23: " << my_functor(23) << std::endl;

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



