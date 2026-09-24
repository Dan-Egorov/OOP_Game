#pragma once
#include "../Robot/robot.hpp"

class Enemy: public Robot {
private:
    bool alive;
public:
    Enemy(int hp, int hpMax, int power, int energy, int maxEnergy,
          int speed, int vision);

    bool isAlive() const;

    void onDeath() override;
};
