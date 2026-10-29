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

bool Player::needsUpgradeChoice() const {
    return needsUpgrade;
}

void Player::clearUpgradeFlag() {
    needsUpgrade = false;
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