#pragma once

#include "gen.h"
#include "Mob.h"

class Mob;

class IAttackBehavior
{
public:
    // pure virtual function:
    virtual void performAttackMethod(Mob* attacker, Mob *who) = 0;
};


class MaceAttack : public IAttackBehavior
{
public:
    virtual void performAttackMethod(Mob* attacker, Mob *who);

};

class SwordAttack : public IAttackBehavior
{
public:
    virtual void performAttackMethod(Mob* attacker, Mob *who);

};

class FireAttack : public IAttackBehavior
{
public:
    virtual void performAttackMethod(Mob* attacker, Mob *who);

};