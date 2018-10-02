#include "Mob.h"

void Mob::attack(Mob *who)
{
    // std:cout << this->getName() << " hits " << this->getHP() << " ->" << who->getName() << "\n";
    this->_behavior->performAttackMethod(this, who);
}

void Mob::setAttackBehavior(IAttackBehavior* b)
{
    this->_behavior = b;
}
