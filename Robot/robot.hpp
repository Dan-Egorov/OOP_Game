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
public:
    Robot(int hp, int hpMax, int power, int energy, int maxEnergy, BotType type);

    int getHp() const;
    int getHpMax() const;
    int getPower() const;
    int getEnergy() const;
    int getMaxEnergy() const;
    int getExp() const;
    int getExpNewRang() const;
    int getRank() const;
    int getType() const;
    int  getSpeed() const;
    std::pair<int, int> getPosition() const;

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

    void botAttack(Robot &other);
    void botHeal(Robot &other);

    void rankUp(int newRank);

    void botAction(Robot &other);
};
