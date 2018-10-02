#include "utils.h"

void print_message()
{
    std::cout << "This is a native C++ program." << std::endl;
}

void printHex(int a)
{
    std::cout << std::hex << "0x" << a << "\n";
}

void printHex(std::string a)
{
    unsigned int k;
    for (int i = 0; i<a.size(); i++)
    {
        k = (unsigned int)a[i];
        std::cout << " 0x" << std::hex << std::uppercase  << k;        
        // cout << hex << k;
    }
    std::cout << "\n";
}

/*==============================================================================
  Function   : dispBitsToArr()
  Purpose    : print bits to a given array
  Params     : value to print, char array
  Return     : none
  ==============================================================================*/
void dispBitsToArr(unsigned Val, char* _array)
{
    unsigned BIT = 7;
    unsigned   c;
    unsigned   dispMask=1<<BIT;
    int        nBin;
    int nPrintRes = 1;

    //if (nPrintRes)
    //   fprintf (fi, "Val = %d(0x%X)\n", Val, Val);

    for (c = 1; c<=BIT+1; c++)
    {
        nBin = Val & dispMask ? '1' : '0' ;
        _array[c-1] = nBin;
        Val <<= 1;

        if ((c%9 == 0) && nPrintRes)
        {
            _array[c-1] = ' ';
        }
    }

    /* usage:
    char _array_bit[9] = {'0','0','0','0','0','0','0','0','\0'};
    dispBitsToArr(RCON, _array_bit);        
    printf("_array_bit after: \n");
    for (int i=0; i<16; i++)
    {
        // printf ("[%d] = 0x%X\n", i, _array_bit[i]);
        printf ("%c", _array_bit[i]);
    }
    */
}

class FlyBehavior
{
public:
    virtual void fly() = 0;
};

class FlyWithWings: public FlyBehavior
{
public:    
    void fly() { cout << "I'm flying!" << endl; }
};

class FlyNoWay: public FlyBehavior
{
public:
    void fly() { cout << "I can not fly!" << endl; }
};

class FlyRocketPowered: public FlyBehavior
{
public:
    void fly() { cout << "I am flying with a ROCKET!" << endl; }
};

class QuackBehavior
{
public:
    virtual void quack() = 0;
};

class Quack: public QuackBehavior
{
public:    
    void quack() { cout << "Quack!" << endl; }
};

class MuteQuack: public QuackBehavior
{
public:
    void quack() { cout << ".......silence......." << endl; }
};

class Squeak: public QuackBehavior
{
public:
    void quack() { cout << "Squeak!" << endl; }
};

class Duck
{   
public:    
    FlyBehavior *flyBehavior;
    QuackBehavior *quackBehavior;

    Duck(){ }
    virtual void display() = 0;

    void performFly()
    {
        flyBehavior->fly();
    }

    void performQuack()
    {
        quackBehavior->quack();
    }

    void swim()
    {
        cout << "All ducks float. Even decoy." << endl;
    }

    void setFlyBehavior (FlyBehavior *fb)
    {
        this->flyBehavior = fb;
    }

    void setQuackBehavior (QuackBehavior *qb)
    {
        this->quackBehavior = qb;
    }
};


class MallarDuck: public Duck
{
public:
    MallarDuck() 
    {
        quackBehavior = new MuteQuack();
        flyBehavior = new FlyWithWings();
    }
    void display() { cout << "I am a real Mallar Duck." << endl; }
};


class ModelDuck: public Duck
{
public:
    ModelDuck() 
    {
        quackBehavior = new Quack();
        flyBehavior = new FlyNoWay();
    }
    void display() { cout << "I am a real model Duck." << endl; }
};
