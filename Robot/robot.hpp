#pragma once
#include <utility>

enum BotType {
    PLAYER,
    ENEMY
};

class Robot {
private:
    int hp;
    int hpMax;
    int power;
    int energy;
    int maxEnergy;
    int exp;
    int expNewRang;
    int rank;
    int speed;
    std::pair<int, int> position;
    BotType type;
    int vision;
public:
    Robot(int hp, int hpMax, int power, int energy, int maxEnergy, BotType type);

    int getHp() const ;
    int getHpMax();
    int getPower();
    int getEnergy();
    int getMaxEnergy();
    int getExp();
    int getExpNewRang();
    int getRank();
    int getType();
    int  getSpeed();
    int getVision();
    std::pair<int, int> getPosition();

    void setHp(int newHp);
    void setPower(int newPower);
    void setEnergy(int newEnerqy);
    void setMaxEnergy(int newMaxEnergy);
    void setExp(int newExp);
    void setExpNewRang(int newExpNewRang);
    void setRank(int newRank);
    void setType(BotType newType);
    void setPosition(std::pair<int, int> newPosition);
    void setSpeed(int newSpeed);
    void setVision(int newVision);

    void botAttack(Robot &other);
    void botHeal(Robot &other);

    void rankUp(int newRank);

    void botAction(Robot &other);
};
