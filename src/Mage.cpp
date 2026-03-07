#include "Mage.h"

#include <iostream>

Mage::Mage(const std::string& name)
    : Character(name, 80, 35) {}

int Mage::attack() const 
{
    return getAttackPower();
}

int Mage::specialAbility() const {
    std::cout << getName() << " uses Arcane Storm!" << '\n';
    return getAttackPower() + 20;
}