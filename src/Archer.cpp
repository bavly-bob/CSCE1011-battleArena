#include "Archer.h"
#include <iostream>
using namespace std;

Archer::Archer(const std::string& name)
    : Character(name, 100, 45) {}

int Archer::attack() const 
{
    return getAttackPower();
}

int Archer::specialAbility() const {
    cout << getName() << " uses Double Shot!" << '\n';
    return getAttackPower()*2;
}