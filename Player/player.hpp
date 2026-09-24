#pragma once
#include "../Robot/robot.hpp"

class Player : public Robot {
private:
    int exp;
    int expNewRang;
    int rank;
public:
    Player(int hp, int hpMax, int power, int energy, int maxEnergy,
           int speed, int vision);

    int getExp() const;
    int getExpNewRang() const;
    int getRank() const;

    void addExp(int amount);
    void rankUp();

    void onKill() override;
};