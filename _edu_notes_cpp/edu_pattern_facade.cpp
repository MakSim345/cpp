
Facade pattern: provides a unified - simplified interface to a complex subsystem or set of interfaces. It provides a higher level interface simultaneously decoupling the client from the complex subsystem.

An example to help you understand .. a cab driver. You tell the cab driver "Take me to PointX" (unified simplified high-level interface) who then begins on a sequence of actions (turns the key, changes gears, presses the accelerator, etc...) to perform the task. 
He abstracts away the complexity of underlying subsystems (gearbox, engine, etc.) so that you don't have to worry about them. The driver also decouples you from the actual vehicle used... you do not directly interface with the car. You could potentially give him a Merc but your interface to the Driver would still be TakeMeTo( X ).. you're not tied down to any specific model/make of the car.

In a real world example, you'll find facades where you interface with third party components or libraries. You don't want your code to depend on a specific vendor, so you introduce a facade interface to decouple. Also you'll simplify this interface, e.g. your facade interface would have a method called SendData( string ) but internally the implementation may call n methods on m sub-packages in a specific order to get the task done. This is what the diagram on the wikipedia page shows.

e.g. Translating an example to C++ and keeping it tiny

sResource = LWCPPSimple::get("http://www.perl.org")

Here the fictitious Library For WWW in C++ is a facade that unifies protocol, network and parsing aspects of the problem so that I can concentrate on my primary focus of fetching the resource. The get method hides/encapsulates/keeps-in-one-place the complexity (and in some cases ugliness) of HTTP, FTP and other varied protocols, request-response, connection management, etc. Also if tomorrow the creators of LWCPPSimple find a way to make get() to be twice as fast, I get the performance benefits for free. My client code doesn't have to change.


-----
class Engine
{

public:
    void Start() { }

};

class Headlights
{

public:
    void TurnOn() { }

};

//  That's your facade.
class Car
{

private:
    Engine engine;
    Headlights headlights;

public:
    void TurnIgnitionKeyOn()
    {
        headlights.TurnOn();
        engine.Start();
    }

};

int Main(int argc, char *argv[])
{
    //  Consuming facade.
    Car car;
    car.TurnIgnitionKeyOn();

    return 0;
}


