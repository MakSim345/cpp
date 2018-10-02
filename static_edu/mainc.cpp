#include "gen.h"
#include "deck.h"
#include "IDGenerator.h"
using namespace std;

// class IDGenerator;

//int add(int x, int y, int z);

class A
{
public:
    virtual void foo() {cout << "*A foo called." << endl;}
};

class B : public A
{
public:
    virtual void foo() {cout << "-B foo called." << endl;}
};


void squareByReference(int &iRef)
{
    iRef *= iRef;
}

void squareByRef(int *iRef)
{
    *iRef *= *iRef;
}

int add(int x, int y, int z)
{
    return x + y + z;
}

int main( int argc, char *argv[] )
{
    srand (time(NULL));

    // deck _deck = deck();
    // _deck.shuffle();
    // _deck.print_deck();

    // Test staic class variable:
    IDGenerator *cFirst = new IDGenerator();
    IDGenerator *cSecond;
    IDGenerator *cThird;

    cout << "cFirst->GetID() = "<< cFirst->GetID() << endl;
    cout << "cSecond->GetID() = "<< cSecond->GetID() << endl;
    cout << "cThird->GetID() = "<< cThird->GetID() << endl;

    printf ("%x" ,-1<<4);

    A *b = new B();
    b->A::foo ();
    /*
    cout << "3 + 4 + 5 = " << add(3, 4, 5) << endl;
    int z = 4;
    cout << "before: z = "<< z << endl;
    squareByReference(z);
    cout << "after: z = "<< z << endl;

    int zz = 16;
    cout << "before: zz = "<< zz << endl;
    squareByRef(&zz);
    cout << "after: zz = "<< zz << endl;
    */
    return 0;
}


