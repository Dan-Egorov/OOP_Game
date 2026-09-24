#include "player.hpp"

Player::Player(int hp, int hpMax, int power, int energy, int maxEnergy,
               int speed, int vision): Robot(hp, hpMax, power, energy, maxEnergy, speed, vision, PLAYER),
      exp(0), expNewRang(10), rank(1) {}

int Player::getExp() const {
    return exp;
}
int Player::getExpNewRang() const {
    return expNewRang;
}
int Player::getRank() const {
    return rank;
}

void Player::addExp(int new_exp) {
    exp += new_exp;
    while (exp >= expNewRang) {
        exp -= expNewRang;
        rankUp();
    }
}

void Player::rankUp() {
    rank++;
    hpMax += 10;
    hp = hpMax;
    power += 2;
    maxEnergy += 5;
    expNewRang = expNewRang * 2;
}

void Player::onKill() {
    addExp(1);
}