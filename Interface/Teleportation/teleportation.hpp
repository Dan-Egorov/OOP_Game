#pragma once
#include <string>
#include <vector>
#include <utility>
#include "../Interface/interface.hpp"

class Teleportation : public Ability {
private:
    int range;
    int usedEnergy;
public:
    Teleportation(int range, int energyCost);

    std::string getName() override;
    int getUsedEnergy() override;

    std::vector<std::pair<int,int>> collectValidCells(Player& user, Map& map);

    void applyTeleport(Player& user, std::pair<int,int> cell);

    void use(Player&, Map&, Enemy*) override {}
};