#include "robot.hpp"
#include "../Status/Shield/shield.hpp"
#include "../Ability/interface.hpp"

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

const std::vector<std::shared_ptr<Ability>>& Robot::getAbilities() const {
    return abilities;
}
std::vector<std::shared_ptr<Ability>>& Robot::getAbilities() {
    return abilities;
}


void Robot::setHp(int newHp) {
    if (newHp >= hpMax) newHp = hpMax;
    hp = newHp;
}
void Robot::setPower(int newPower) {
    power = newPower;
}
void Robot::setEnergy(int newEnergy) {
    if (newEnergy >= maxEnergy) newEnergy = maxEnergy;
    energy = newEnergy;
}
void Robot::setMaxEnergy(int newMaxEnergy) {
    maxEnergy = newMaxEnergy;
}
void Robot::setSpeed(int newSpeed) {
    if (newSpeed < 0) newSpeed = 0;
    speed = newSpeed;
}
void Robot::setVision(int newVision) {
    if (newVision < 1) newVision = 1;
    vision = newVision;
}
void Robot::setPosition(std::pair<int, int> newPosition) {
    position = newPosition;
}

int Robot::getAbilityCount() const {
    return abilities.size();
}

void Robot::addAbility(std::shared_ptr<Ability> a) {
    abilities.push_back(std::move(a));
}

bool Robot::hasAbility(AbilityType type) const {
    for (const auto& a : abilities)
        if (a->getType() == type) return true;
    return false;
}

void Robot::botAttack(Robot& other) {
    other.takeDamage(power);

    if (other.getHp() <= 0) {
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

void Robot::addStatus(std::shared_ptr<Status> s) {
    if (!s) return;

    for (auto& existing : statuses) {
        if (existing->getType() == s->getType()) {
            existing->merge(*s);
            return;
        }
    }

    s->apply(*this);
    statuses.push_back(s);
}

void Robot::removeStatus(StatusType t) {
    for (auto it = statuses.begin(); it != statuses.end(); it++) {
        if ((*it)->getType() == t) {
            (*it)->remove(*this);
            statuses.erase(it);
            return;
        }
    }
}

bool Robot::hasStatus(StatusType t) const {
    for (const auto& s : statuses)
        if (s->getType() == t) return true;
    return false;
}

std::shared_ptr<Status> Robot::getStatus(StatusType t) {
    for (auto& s : statuses)
        if (s->getType() == t) return s;
    return nullptr;
}

void Robot::tickStatuses() {
    for (auto& s : statuses)
        s->tick(*this);

    for (auto it = statuses.begin(); it != statuses.end(); ) {
        if ((*it)->isExpired()) {
            (*it)->remove(*this);
            it = statuses.erase(it);
        } else {
            it++;
        }
    }
}

void Robot::takeDamage(int amount) {
    if (auto sh = getStatus(Shield_st)) {
        auto* shield = static_cast<Shield*>(sh.get());
        amount = shield->absorb(amount);
        if (shield->isExpired()) removeStatus(Shield_st);
    }

    if (amount <= 0) return;

    int newHp = getHp() - amount;
    if (newHp < 0) newHp = 0;
    setHp(newHp);

    if (getHp() <= 0) onDeath();
}