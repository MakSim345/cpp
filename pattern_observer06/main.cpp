//

#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

// forward declaration:
// class ObserverIf;

// ----------------The Observer interface -----------------
class ObserverIf
{
public:
    virtual void update(const std::string& message) = 0; //pure virtual function
    virtual ~ObserverIf() = default; // virtual destructor for proper clean up
};

class ConcreteObserver : public ObserverIf
{
public:
    // Constructor:
    ConcreteObserver(const std::string& nameP): nameM(nameP) {}

    //
    void update(const std::string& message) override
    {
        std::cout << "Observer " << nameM << " received message: " << message << std::endl;
    }

private:
    std::string nameM;
};

//The subject class:
class Subject
{
public:
    void attach(ObserverIf* pObserverP)
    {
        vectorOfObservers.push_back(pObserverP);
    }

    void notify(const std::string& messageP)
    {
        for (ObserverIf* oneObserverFromVector : vectorOfObservers)
        {
            oneObserverFromVector->update(messageP);
        }
    }

private:
    std::vector<ObserverIf*> vectorOfObservers;
};


int main()
{
    Subject listOfListeners;

    ConcreteObserver listener1("listener1");
    ConcreteObserver listener2("listener2");

    listOfListeners.attach(&listener1);
    listOfListeners.attach(&listener2);

    listOfListeners.notify("Hello, listeners!");
    // system("PAUSE");
    return 0;
}

