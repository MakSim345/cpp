#include "gen.h"
#include "cube_calc.h"
#include "base.h"

using namespace std;

inline float cube(const float s) {return s*s*s;}

class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make some product...\n";
        show_who(baseClassObject);
        show_who(firstDerivedObject);
        show_who(secondDerivedObject);
        return 0;
    }

    App()
    {

        baseClassObject = baseClass();
        firstDerivedObject = firstDerivedClass();
        secondDerivedObject = secondDerivedClass();
    }

    ~App()
    {
        std::cout << "Good bye!\n";
    }

    void show_who(baseClass &value)
    {
        value.who();
    }

private:
    baseClass baseClassObject;
    firstDerivedClass firstDerivedObject;
    secondDerivedClass secondDerivedObject;
};

int test_foo()
{
    LOG_TRACE;
    int i = 0;
    i++;
    return i;
}

void test_CallFunction()
{
    mathBaseClass mathBase;
    cout << "mathBase.CallFunction(5) = " << mathBase.CallFunction(5)<< endl;      // 11
    mathDerivedClass mathDerived;
    cout << "mathDerived.CallFunction(5) = " << mathDerived.CallFunction(5)<< endl;      // which f() to call?
}

void settime(Clock &d)    
{
    d.print(); // assuming Base class calling
}

void test_Clock()
{
    std::cout << "Create Clock:" << std::endl;
    Clock baseClock;                  // base class object
    settime(baseClock);               // print "Clock"

    std::cout << "Create Alarm:" << std::endl;
    Alarm derivedAlarm;                  // derived class object
    settime(derivedAlarm);               // referring to derived class, not base!

    std::cout << "Create Clock *baseClock02:" << std::endl;    
    Clock *baseClock02 = &baseClock;// the address of a base class object
    std::cout << "baseClock02->print()" << std::endl;
    baseClock02->print();               // calling base class method!
    

    std::cout << "Reassign baseClock02 = &derivedAlarm:" << std::endl;
    // Clock *baseClock02 = new Alarm();
    baseClock02 = &derivedAlarm;        // the address of a derived class instead of base class
    baseClock02->print();               // which method will call, base or derived?
}

void test_Cats()
{
    Cat *cats[] = {new Cat, new CheshireCat};
    std::cout << "Ordinary Cat:" << std::endl; cats[0]->AskForFood();
    std::cout << "CheshireCat" << std::endl; cats[1]->AskForFood();

    delete cats[0];
    delete cats[1];
}


int main()
{
    test_Cats();
    // test_Clock();

    // test_CallFunction();

    // CubeCalc *cube_calc = new CubeCalc();
    //std::auto_ptr <CubeCalc> cube_calc(new CubeCalc());
    //cube_calc->run();

    //std::auto_ptr <App> virt_test(new App());
    //virt_test->Run();
    
    // test_foo();    

    printf ("Application complete.\n");
    system ("PAUSE");
    return 1;
}
