#pragma once

#include "Character.h"

class Mage : public Character {
public:
    explicit Mage(const std::string& name);

    int attack() const override;
    int specialAbility() const override;
};

