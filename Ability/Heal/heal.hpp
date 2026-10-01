#pragma once
#include "../interface.hpp"

class Heal : public Ability {
private:
    int newHp;
    int usedEnergy;
public:
    Heal(int heal, int energy);

    std::string getName() override;
    int getUsedEnergy() override;
    AbilityType getType() const override;
    void use(Player& robot, Map& map, Enemy* target) override;
    void upgrade() override;
};