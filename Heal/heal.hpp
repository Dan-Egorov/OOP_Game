#pragma once
#include "../Interface/interface.hpp"

class Heal: public Ability {
private:
    int newHp;
    int usedEnergy = 0;
public:
    Heal(int hp, int e);

    int getUsedEnergy() override;
    std::string getName() override;

    void use(Player &robot, Map &map, Enemy* target = nullptr) override;
};