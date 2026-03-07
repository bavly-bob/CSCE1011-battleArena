#pragma once
#include <string>

class Character {
public:
    Character(const std::string& name, int health, int attackPower);
    ~Character();

    std::string getName() const;
    virtual int attack() const = 0;
    virtual int specialAbility() const = 0;

    void takeDamage(int damage);
    bool isAlive() const;

    int getHealth() const;  // Added to public to use in main.cpp for stats tracking

    static int getCharacterCount();

private:
    std::string name;
    int health;
    int attackPower;
    static int characterCount;

protected:
    int getAttackPower() const;


};

