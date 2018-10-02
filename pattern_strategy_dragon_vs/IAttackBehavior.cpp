#include "IAttackBehavior.h"

void MaceAttack::performAttackMethod(Mob* attacker, Mob *who)
{
    std:cout << attacker->getName() << " crushes " << attacker->getHP() << " ->" << who->getName() << "\n";
}

void SwordAttack::performAttackMethod(Mob* attacker, Mob *who)
{
    std:cout << attacker->getName() << " slashes " << attacker->getHP() << " ->" << who->getName() << "\n";
}

void FireAttack::performAttackMethod(Mob* attacker, Mob *who)
{
    std:cout << attacker->getName() << " scorches " << attacker->getHP() << " ->" << who->getName() << "\n";
}
