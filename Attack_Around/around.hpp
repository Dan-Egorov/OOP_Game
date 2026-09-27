#pragma once
#include <string>
#include "../Interface/interface.hpp"

class Around: public Ability {
private:
    int damage;
    int usedEnergy;
public:
    Around(int damag, int e);
    std::string getName() override;
    int getUsedEnergy() override;
    void use(Player &robot, Map &map, Enemy* target = nullptr) override;
    //void use(Player &robot, std::vector<Enemy*> &enemies) override;
};