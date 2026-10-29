#pragma once
#include <string>
#include "../interface.hpp"

class Around : public Ability {
private:
    int damage;
    int radius;
    int usedEnergy;
public:
    Around(int damage, int radius, int energy);

    std::string getName() override;
    int getUsedEnergy() override;
    AbilityType getType() const override;
    void use(Robot& robot, Map& map, Enemy* target) override;
    void upgrade() override;
};