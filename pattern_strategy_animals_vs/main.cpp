#include "gen.h"
#include "utils.h"
#include "animals.h"

int main()
{
    cout << "APP start:" << endl;

    Animal *sparky = new Dog();
    Animal *tweety = new Bird();

    cout << "Dog: " << endl;
    sparky->tryTofly();

    cout << "Bird: " << endl;
    tweety->tryTofly();

    // This allows dynamic changes for FlyBehavior:

    sparky->setFlyingAbility(new FlyCanDo());
    cout << "Dog (matrix): " << endl;
    sparky->tryTofly();


    cout << "APP end." << endl;

    system("PAUSE");
}


