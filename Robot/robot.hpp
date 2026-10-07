#pragma once
#include <memory>
#include <utility>
#include <vector>
#include "../Status/status.hpp"

enum BotType {
    PLAYER,
    ENEMY
};

class Robot {
protected:
    int hp;
    int hpMax;
    int power;
    int energy;
    int maxEnergy;
    int speed;
    int vision;
    std::pair<int, int> position;
    BotType type;
    std::vector<std::shared_ptr<Status>> statuses;
    bool overloaded = false;
public:
    Robot(int hp, int hpMax, int power, int energy,
        int maxEnergy, int speed, int vision, BotType type);
    virtual ~Robot() = default;

    int getHp() const;
    int getHpMax() const;
    int getPower() const;
    int getEnergy() const;
    int getMaxEnergy() const;
    int getSpeed() const;
    int getVision() const;
    BotType getType() const;
    std::pair<int, int> getPosition() const;

    void setHp(int newHp);
    void setPower(int newPower);
    void setEnergy(int newEnergy);
    void setMaxEnergy(int newMaxEnergy);
    void setSpeed(int newSpeed);
    void setVision(int newVision);
    void setPosition(std::pair<int, int> newPosition);

    void botAttack(Robot& other);
    void botHeal(Robot& other);
    void botAction(Robot& other);

    virtual void onKill() {}
    virtual void onDeath() {}

    void setOverloaded(bool v) { overloaded = v; }
    bool isOverloaded() const  { return overloaded; }

    void addStatus(std::shared_ptr<Status> s);
    void removeStatus(StatusType t);
    bool hasStatus(StatusType t) const;
    std::shared_ptr<Status> getStatus(StatusType t);
    void tickStatuses();

    //void takeDamage(int amount);
};