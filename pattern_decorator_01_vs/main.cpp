#include "gen.h"


class BeverageBase
{    
public:

    BeverageBase():
      myDescription("BeverageBase class"),
      milkPrice(50),
      sugarPrice(10),
      chocolatePrice(70)
    {};

    string getDescription() {return myDescription;}
    
    virtual double getCost()
    {
        double cost = 0;
        if (hasMilk())
            cost = cost + milkPrice;
        if (hasChocolate())
            cost = cost + chocolatePrice;        
        if (hasShugar())
            cost = cost + sugarPrice;

        return cost;
    }

    virtual bool hasShugar()=0;
    virtual bool hasMilk()=0;
    virtual bool hasChocolate()=0;

protected:
    string myDescription;
    double milkPrice;
    double sugarPrice;
    double chocolatePrice;
    double basePrice;
};

class Espresso: public BeverageBase
{
public:
    Espresso()
      {basePrice = 50;}

    double getCost()
    {
        return basePrice + BeverageBase::getCost();
    }
    virtual bool hasShugar()   {return false;}
    virtual bool hasMilk()     {return false;}
    virtual bool hasChocolate(){return false;}

protected:
};

class HotChocolate: public BeverageBase
{
public:
    HotChocolate()
    {basePrice = 150;}

    double getCost()
    {
        return basePrice + BeverageBase::getCost();
    }
    virtual bool hasShugar()   {return true;}
    virtual bool hasMilk()     {return true;}
    virtual bool hasChocolate(){return true;}

protected:
};

class BlackTea: public BeverageBase
{
public:
    BlackTea()     
    {
        basePrice = 25;
        myDescription ="Black tea";
    }

    double getCost()
    {
        return basePrice + BeverageBase::getCost();
    }
    virtual bool hasShugar()   {return true;}
    virtual bool hasMilk()     {return false;}
    virtual bool hasChocolate(){return false;}

protected:
};

class Capuccino: public BeverageBase
{
public:
    double getCost()
    {
        return 120 + BeverageBase::getCost();
    }
    virtual bool hasShugar()   {return true;}
    virtual bool hasMilk()     {return true;}
    virtual bool hasChocolate(){return false;}

protected:
};

/*
    void printMe()
    {
        std::cout << windowM << "\n";
        std::cout << doorM << "\n";
        std::cout << bathroomM << "\n";
        std::cout << kitchenM << "\n";
        std::cout << floorM << "\n";
    }
*/


class MainApp
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make some product...\n";
        BeverageBase *espresso = new Espresso();
        std::cout<<"-------------------Espresso Constructed. \n";
        double e_cost = espresso->getCost();
        std::cout <<"Cost: " << e_cost << "\n";


        BeverageBase *black_tea = new BlackTea();
        std::cout<<"-------------------Black Tea Constructed. \n";
        e_cost = black_tea->getCost();
        std::cout <<"Cost: " << e_cost << "\n";


        BeverageBase *capuccino = new Capuccino();
        std::cout<<"-------------------capuccino Constructed. \n";
        e_cost = capuccino->getCost();
        std::cout <<"Cost: " << e_cost << "\n";

        
        return 0;
    }

    ~MainApp()
    {
        std::cout << "App: Good bye!\n";
    }

};


int main()
{
    
    std::auto_ptr <MainApp> _builder(new MainApp());
    
    _builder->Run();
    
    system ("PAUSE");
    return 1;
}
