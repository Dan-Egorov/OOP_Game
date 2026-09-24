#include "robot.hpp"

Robot::Robot(int hp, int hpMax, int power, int energy, int maxEnergy,
             int speed, int vision, BotType type) : hp(hp), hpMax(hpMax),
    power(power),energy(energy), maxEnergy(maxEnergy), speed(speed), vision(vision), type(type) {}

int Robot::getHp() const {
    return hp;
}
int Robot::getHpMax() const {
    return hpMax;
}
int Robot::getPower() const {
    return power;
}
int Robot::getEnergy() const {
    return energy;
}
int Robot::getMaxEnergy() const {
    return maxEnergy;
}
int Robot::getSpeed() const {
    return speed;
}
int Robot::getVision() const {
    return vision;
}
BotType Robot::getType() const {
    return type;
}
std::pair<int, int> Robot::getPosition() const {
    return position;
}

void Robot::setHp(int newHp) {
    hp = newHp;
}
void Robot::setPower(int newPower) {
    power = newPower;
}
void Robot::setEnergy(int newEnergy) {
    energy = newEnergy;
}
void Robot::setMaxEnergy(int newMaxEnergy) {
    maxEnergy = newMaxEnergy;
}
void Robot::setSpeed(int newSpeed) {
    if (newSpeed < 1) newSpeed = 1;
    speed = newSpeed;
}
void Robot::setVision(int newVision) {
    if (newVision < 1) newVision = 1;
    vision = newVision;
}
void Robot::setPosition(std::pair<int, int> newPosition) {
    position = newPosition;
}

void Robot::botAttack(Robot& other) {
    int new_hp = other.getHp() - power;
    if (new_hp < 0) new_hp = 0;
    other.setHp(new_hp);
    if (other.getHp() <= 0) {
        other.onDeath();
        onKill();
    }
}

void Robot::botHeal(Robot& other) {
    int new_hp = other.getHp() + power;
    if (new_hp > other.getHpMax()) new_hp = other.getHpMax();
    other.setHp(new_hp);
}

void Robot::botAction(Robot& other) {
    if (other.getType() != type) botAttack(other);
    else botHeal(other);
}