#include "gen.h"

class Sauce;
class Topping;
class Cheese;


class Sauce
{
public:
    Sauce(string p) 
    {
        this->p = p;
    }

    string name() {return p;}

private:
    string p;

};

class Topping
{
public:
    Topping(string p) 
    {
        this->p = p;
    }
    
    string name() {return p;}

private:
    string p;
};

class Cheese
{
public:
    Cheese(string p) 
    {
        this->p = p;
    }
    
    string name() {return p;}
private:
    string p;
};


class Dough
{
public:
    Dough():
      p("Pizza with ")
      {
          /**/;
      }
    
    void addSauce(Sauce *sauce) 
    {
        std::cout << "add sauce: " << sauce->name() << "\n";
        p = p + sauce->name() + " + ";
    }
    
    void addTopping(Topping *topping) 
    {
        std::cout << "add topping: " << topping->name() << "\n";
        p = p + topping->name() + " + ";
    }

    void addCheese(Cheese *cheese) 
    {
        std::cout << "add cheese: " << cheese->name() << "\n";
        p = p + cheese->name();
    }

    string name() {return p;}

private:
    string p;

};

class Owen
{
public:
    void setTemperature(int temp) {/**/;}
    void setTimer(int min) {/**/;}
    void cookProduct(Dough *dough) 
    {
        std::cout << "Make a product: " << dough->name() << "\n";
    }
};

class PizzaFacade
{

public:

    PizzaFacade(Dough *dough, Sauce *sauce, Topping *top, Cheese *cheese)
    {
        this->dough = dough;
        this->sauce = sauce;
        this->top = top;
        this->cheese = cheese;
    }

    void makePizza()
    {
        // owen = new Owen();
        dough->addSauce(sauce);
        dough->addTopping(top);
        dough->addCheese(cheese);        
        owen->setTemperature(245);
        owen->setTimer(20);
        owen->cookProduct(dough);
    }
private:
    Dough *dough;
    Sauce *sauce;
    Topping *top;
    Cheese *cheese;
    Owen *owen;
};


class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make PIZZA FACADE\n";        
        Client1();
        Client2();
        return 0;
    }

    void Client1()
    {
        Dough *dough = new Dough();
        Sauce *sauce = new Sauce("Tomato");
        Topping *top = new Topping("Mushrooms");
        Cheese *cheese = new Cheese("Mozzarella");
        Owen *owen = new Owen();

        PizzaFacade *pizzaFacade = new PizzaFacade(dough, sauce, top, cheese);
        pizzaFacade->makePizza();

        /*
        dough->addSauce(sauce);
        dough->addTopping(top);
        dough->addCheese(cheese);        
        owen->setTemperature(245);
        owen->setTimer(20);
        owen->cookProduct(dough);
        */
    }

    void Client2()
    {
        Dough *dough = new Dough();
        Sauce *sauce = new Sauce("Tomato");
        Topping *top = new Topping("Olives");
        Cheese *cheese = new Cheese("Mozzarella");
        Owen *owen = new Owen();

        dough->addSauce(sauce);
        dough->addTopping(top);
        dough->addCheese(cheese);        
        owen->setTemperature(245);
        owen->setTimer(20);
        owen->cookProduct(dough);
    }

    ~App()
    {
        std::cout << "\nGood bye!\n";
    }

};

int main()
{
    std::auto_ptr <App> my_facade(new App());

    try
    {
        my_facade->Run();
    }
    catch(std::runtime_error)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER\n";
    }
    /*
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER has number - " << EXCEPTION_EXECUTE_HANDLER << "\n";
    }    
    */
    system("PAUSE");
    return 1;
}
