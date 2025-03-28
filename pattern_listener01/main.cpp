//

#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

// forward declaration:
// class ListenerIf;
// class ConcreteListener;

// ----------------The Listener interface -----------------
class ListenerIf
{
public:
    virtual void update(const std::string& message) = 0; //pure virtual function
    virtual ~ListenerIf() = default; // virtual destructor for proper clean up
};

class ConcreteListener : public ListenerIf
{
public:
    // Constructor:
    ConcreteListener(const std::string& nameP): nameM(nameP) {}

    //
    void update(const std::string& message) override
    {
        std::cout << "Listener named '" << nameM << "' received message: " << message << std::endl;
    }

private:
    std::string nameM;
};


// ----------------The Subject class -----------------
class Subject
{
public:
    void attach(ListenerIf* pListenerP)
    {
        vectorOfListeners.push_back(pListenerP);
    }

    void notify(const std::string& messageP)
    {
        for (ListenerIf* oneListenerFromVector : vectorOfListeners)
        {
            oneListenerFromVector->update(messageP);
        }
    }

private:
    std::vector<ListenerIf*> vectorOfListeners;
};


int main()
{
    Subject listOfListeners;

    ConcreteListener listener1("Listener-1");
    ConcreteListener listener2("Listener-2");

    listOfListeners.attach(&listener1);
    listOfListeners.attach(&listener2);

    listOfListeners.notify("Hello, listeners!");
    // system("PAUSE");
    return 0;
}

