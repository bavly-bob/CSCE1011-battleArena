#pragma once
#include "Character.h"

class Warrior : public Character {
public:
    explicit Warrior(const std::string& name);

    int attack() const override;
    int specialAbility() const override;
};
