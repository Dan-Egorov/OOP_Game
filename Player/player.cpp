#include "player.hpp"

Player::Player(int hp, int hpMax, int power, int energy, int maxEnergy,
               int speed, int vision): Robot(hp, hpMax, power, energy, maxEnergy, speed, vision, PLAYER),
      exp(4), expNewRang(5), rank(1) {}

int Player::getExp() const {
    return exp;
}
int Player::getExpNewRang() const {
    return expNewRang;
}
int Player::getRank() const {
    return rank;
}

int Player::getAbilityCount() const {
    return abilities.size();
}

bool Player::needsUpgradeChoice() const {
    return needsUpgrade;
}

void Player::clearUpgradeFlag() {
    needsUpgrade = false;
}

void Player::addAbility(std::unique_ptr<Ability> a) {
    abilities.push_back(std::move(a));
}

bool Player::hasAbility(AbilityType type) const {
    for (const auto& a : abilities)
        if (a->getType() == type) return true;
    return false;
}

const std::vector<std::unique_ptr<Ability>>& Player::getAbilities() const {
    return abilities;
}
std::vector<std::unique_ptr<Ability>>& Player::getAbilities() {
    return abilities;
}

void Player::rankUp() {
    rank++;
    hpMax += 10;
    hp = hpMax;
    power += 2;
    maxEnergy += 5;
    expNewRang *= 2;
    needsUpgrade = true;
}

void Player::addExp(int amount) {
    exp += amount;
    while (exp >= expNewRang) {
        exp -= expNewRang;
        rankUp();
    }
}

void Player::onKill() {
    addExp(1);
}