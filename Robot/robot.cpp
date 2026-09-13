#include "robot.hpp"

//Constructure
Robot::Robot(int hp, int hpMax, int power, int energy, int maxEnergy, BotType type)
    : hp(hp), hpMax(hpMax), power(power),
      energy(energy), maxEnergy(maxEnergy),
      type(type), exp(0), expNewRang(10), speed(3), vision(1) {}

// Getters realization
int Robot::getEnergy() const {
    return energy;
}

int Robot::getPower() const {
    return power;
}

int Robot::getMaxEnergy() const {
    return maxEnergy;
}

int Robot::getHp() const {
    return hp;
}

int Robot::getHpMax() const {
    return hpMax;
}

int Robot::getExp() const {
    return exp;
}

int Robot::getExpNewRang() const {
    return expNewRang;
}

int Robot::getRank() const {
    return rank;
}

int Robot::getType() const {
    return type;
}

std::pair<int, int> Robot::getPosition() const {
    return position;
}

int Robot::getSpeed() const {
    return speed;
}

int Robot::getVision() const {
    return vision;
}

//Setters realization
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

void Robot::setExp(int newExp) {
    exp = newExp;
}

void Robot::setExpNewRang(int newExpNewRang) {
    expNewRang = newExpNewRang;
}

void Robot::setRank(int newRank) {
    rank = newRank;
}

void Robot::setType(BotType newType) {
    type = newType;
}

void Robot::setPosition(std::pair<int, int> newPosition) {
    position = newPosition;
}

void Robot::setSpeed(int newSpeed) {
    if (newSpeed < 1) newSpeed = 1;
    speed = newSpeed;
}

void Robot::setVision(int newVision) {
    if (newVision < 1) newVision = 1;
    vision = newVision;
}

//Attak function realization
void Robot::botAttack(Robot &other) {
    int new_hp = other.getHp() - this->getPower();
    int new_exp = this->getExp() + 1;

    if (new_hp < 0) new_hp = 0;

    this->setExp(new_exp);
    other.setHp(new_hp);
}

//Heal realization
void Robot::botHeal(Robot &other) {
    int new_hp = other.getHp() + this->getPower();
    if (new_hp > hpMax) new_hp = other.getHpMax();
    other.setHp(new_hp);
}

//Choosing actions for bot
void Robot::botAction(Robot &other) {
    if (other.getType() != this->type) this->botAttack(other);
    else this->botHeal(other);
}