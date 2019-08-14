#pragma once

#include "gen.h"
#include "IAttackBehavior.h"

class IAttackBehavior;

class Mob
{
public:
    Mob(std::string name, int hp):
      _name(name),
          _hp(hp),
          _behavior(0)
      {
          // todo implementation
      }

      void attack(Mob *who); // perform our attack.

      void setAttackBehavior(IAttackBehavior* b);

      // various getters and setters for name and HP:
      void setHP(int hp)
      {
          (this->_hp = hp);
      }
      inline int getHP() const
      {
          return (this->_hp);
      }
      const std::string& getName() const
      {
          return this->_name;
      }

protected:
    int _hp;
    std::string _name;

    IAttackBehavior* _behavior;
};


class Client: public Mob
{
public:
    Client(std::string name, int hp): Mob (name, hp)
    {
        // todo implementation
    }

    void networking() {}; // does nothing

};
