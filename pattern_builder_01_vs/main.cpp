#include "gen.h"

#include <iostream>

using namespace std;

/* Interface that will be returned as the product from builder */
class HousePlan
{
public:
    virtual void setWindow(string window)=0;
    virtual void setDoor(string door)=0;
    virtual void setBathroom(string bathroom)=0;
    virtual void setKitchen(string kitchen)=0;
    virtual void setFloor(string floor)=0;
    virtual void printMe() = 0;
};

/* Concrete class for the HousePlan interface */
class House:public HousePlan
{
private :
    string windowM, doorM, kitchenM, bathroomM, floorM;

public:
    void setWindow(string windowP)
    {
        this->windowM = windowP;
        //std::cout << windowM << "\n";
    }

    void setDoor(string doorP)
    {
        this->doorM = doorP;
        //std::cout << doorM << "\n";
    }

    void setBathroom(string bathroomP)
    {
        this->bathroomM = bathroomP;
        //std::cout << bathroomM << "\n";
    }

    void setKitchen(string kitchenP)
    {
        this->kitchenM = kitchenP;
        //std::cout << kitchenM << "\n";
    }

    void setFloor(string floorP)
    {
        this->floorM = floorP;
        //std::cout << floorM << "\n";
    }

    void printMe()
    {
        std::cout << windowM << "\n";
        std::cout << doorM << "\n";
        std::cout << bathroomM << "\n";
        std::cout << kitchenM << "\n";
        std::cout << floorM << "\n";
    }

};

/* Builder Class */
class HouseBuilder
{
public:
    /* Abstract functions to build parts */
    virtual void buildWindow()=0;
    virtual void buildDoor()=0;
    virtual void buildKitchen()=0;
    virtual void buildBathroom()=0;
    virtual void buildFloor()=0;
    /* The product is returned by this function */
    virtual House* getHouse()=0;
};

/* Concrete class for the builder interface */
class LavishHouse:public HouseBuilder
{
private:
    House *house;
public:
    LavishHouse()        {house = new House();}
    void buildWindow()   {house->setWindow("French Window");}
    void buildDoor()     {house->setDoor("Wooden Door");}
    void buildBathroom() {house->setBathroom("Modern Bathroom");}
    void buildKitchen()  {house->setKitchen("Modular Kitchen");}
    void buildFloor()    {house->setFloor("Wooden Floor");}
    House* getHouse()    {return this->house;}
};

/* Another Concrete class for the builder interface */
class NormalHouse:public HouseBuilder
{
private:
    House *house;
public:
    NormalHouse()        {house = new House();}
    void buildWindow()   {house->setWindow("Normal Window");}
    void buildDoor()     {house->setDoor("Metal Door");}
    void buildBathroom() {house->setBathroom("Regular Bathroom");}
    void buildKitchen()  {house->setKitchen("Regular Kitchen");}
    void buildFloor()    {house->setFloor("Mosaic Floor");}
    House* getHouse()    {return this->house;}
};

/* The Director. Constructs the house */
class Contractor
{
private:
    HouseBuilder *houseBuilderM;

public:
    Contractor(HouseBuilder *_rHouseBuilderP)  { this->houseBuilderM = _rHouseBuilderP;}
    House *getHouse() {return houseBuilderM->getHouse();}

    void buildHouse()
    {
        houseBuilderM->buildWindow();
        houseBuilderM->buildDoor();
        houseBuilderM->buildBathroom();
        houseBuilderM->buildKitchen();
        houseBuilderM->buildFloor();
    }
};

class MainApp
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make some product...\n";
        HouseBuilder *lavishHouseBldr = new LavishHouse();
        HouseBuilder *normalHouseBldr = new NormalHouse();

        Contractor *ctr1 = new Contractor(lavishHouseBldr);
        Contractor *ctr2 = new Contractor(normalHouseBldr);

        ctr1->buildHouse();
        House *house1 = ctr1->getHouse();
        cout<<"-------------------Constructed: \n";
        house1->printMe();

        ctr2->buildHouse();
        House *house2 = ctr2->getHouse();
        cout<<"-------------------Constructed: \n";
        house2->printMe();
        
        // r->draw();
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
