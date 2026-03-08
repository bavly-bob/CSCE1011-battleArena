#pragma once
#include "Character.h"

class Archer : public Character {
public:
    explicit Archer(const std::string& name);

    int attack() const override;
    int specialAbility() const override;
};

