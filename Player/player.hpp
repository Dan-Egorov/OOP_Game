#pragma once

#include "../Robot/robot.hpp"
#include "inventory.hpp"

class Player : public Robot {
private:
    int exp;
    int expNewRang;
    int rank;
    bool needsUpgrade = false;
    Inventory inventory;

public:
    Player(int hp, int hpMax, int power, int energy, int maxEnergy,
           int speed, int vision);

    int getExp() const;
    int getExpNewRang() const;
    int getRank() const;

    void receiveItem(std::shared_ptr<Item> item) override;
    Inventory& getInventory();

    bool needsUpgradeChoice() const;
    void clearUpgradeFlag();

    void addExp(int amount);
    void rankUp();

    void onKill() override;
};