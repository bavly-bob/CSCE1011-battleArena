#include "Warrior.h"

#include <iostream>

Warrior::Warrior(const std::string& name)
    : Character(name, 140, 22) {}

int Warrior::attack() const 
{
    return getAttackPower();
}

int Warrior::specialAbility() const 
{
    std::cout << getName() << " uses Power Strike!" << '\n';
    return getAttackPower() + 12;
}