#pragma once
#include <vector>

#include "../Robot/robot.hpp"
#include "../Interface/interface.hpp"

class Player : public Robot {
private:
    int exp;
    int expNewRang;
    int rank;
    std::vector<AbilityType> abilityTypes;
public:
    Player(int hp, int hpMax, int power, int energy, int maxEnergy,
           int speed, int vision);

    int getExp() const;
    int getExpNewRang() const;
    int getRank() const;
    std::vector<AbilityType> getAbilities() const;

    void addNewAbility(AbilityType abilityType);

    void addExp(int amount);
    void rankUp();

    void onKill() override;
};