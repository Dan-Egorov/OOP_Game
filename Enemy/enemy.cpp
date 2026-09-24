#include "enemy.hpp"

Enemy::Enemy(int hp, int hpMax, int power, int energy, int maxEnergy,
             int speed, int vision): Robot(hp, hpMax, power, energy, maxEnergy, speed, vision, ENEMY),
      alive(true) {}

bool Enemy::isAlive() const {
    return alive;
}

void Enemy::onDeath() {
    alive = false;
}