#pragma once
#include <string>
#include <vector>
#include <utility>
#include "../interface.hpp"

class Teleportation : public Ability {
private:
    int range;
    int usedEnergy;
public:
    Teleportation(int range, int energyCost);

    std::string getName() override;
    int getUsedEnergy() override;

    std::vector<std::pair<int,int>> collectValidCells(Robot& user, Map& map);

    void applyTeleport(Robot& user, std::pair<int,int> cell);

    void upgrade() override;

    void use(Robot&, Map&, Enemy*) override {}
    AbilityType getType() const override;
};