#pragma once
#include <vector>
#include <memory>

#include "../Robot/robot.hpp"
#include "../Ability/interface.hpp"

class Player : public Robot {
private:
    int exp;
    int expNewRang;
    int rank;
    std::vector<std::unique_ptr<Ability>> abilities;
    bool needsUpgrade = false;

public:
    Player(int hp, int hpMax, int power, int energy, int maxEnergy,
           int speed, int vision);

    int getExp() const;
    int getExpNewRang() const;
    int getRank() const;

    const std::vector<std::unique_ptr<Ability>>& getAbilities() const;
    std::vector<std::unique_ptr<Ability>>& getAbilities();

    void addAbility(std::unique_ptr<Ability> a);
    bool hasAbility(AbilityType type) const;
    int  getAbilityCount() const;

    bool needsUpgradeChoice() const;
    void clearUpgradeFlag();

    void addExp(int amount);
    void rankUp();

    void onKill() override;
};