#include "Character.h"
#include <iostream>
using namespace std;

int Character::characterCount = 0;

Character::Character(const string& name, int health, int attackPower)
    : name(name), health(health), attackPower(attackPower) { characterCount++; }

Character::~Character() 
{
    characterCount--;
    cout << "Destructor: " << name << " has left the arena." << '\n';
}

string Character::getName() const 
{
    return name;
}

int Character::getAttackPower() const 
{
    return attackPower;
}

int Character::getHealth() const 
{
    return health;
}

void Character::takeDamage(int damage) 
{
    if (damage <= 0)
        return;

    health -= damage;
    if (health < 0) 
        health = 0;

    cout << name << " takes " << damage << " damage. Remaining health: " << health << '\n';
}

bool Character::isAlive() const 
{
    return health > 0;
}

int Character::getCharacterCount() 
{
    return characterCount;
}