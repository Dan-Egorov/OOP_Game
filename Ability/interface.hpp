#pragma once
#include <string>

class Map;
class Player;
class Enemy;
class Robot;

enum AbilityType {
    Around_ab,
    Far_ab,
    Heal_ab,
    Teleport_ab
};

class Ability {
public:
    virtual ~Ability() = default;

    virtual std::string getName() = 0;
    virtual int getUsedEnergy() = 0;
    virtual void use(Robot& user, Map& map, Enemy* target) = 0;

    virtual void upgrade() = 0;
    virtual AbilityType getType() const = 0;
};