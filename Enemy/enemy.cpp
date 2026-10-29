#include "enemy.hpp"
#include "../Ability/Teleportation/teleportation.hpp"
#include "../Ability/Heal/heal.hpp"

Enemy::Enemy(int hp, int hpMax, int power, int energy, int maxEnergy,
             int speed, int vision): Robot(hp, hpMax, power, energy, maxEnergy, speed, vision, ENEMY),
      alive(true) {
    srand(time(0));
    if (rand() % 2 == 0) {
        addAbility(std::make_shared<Heal>(10, 5));
    } else {
        addAbility(std::make_shared<Teleportation>(2, 5));
    }
}

bool Enemy::isAlive() const {
    return alive;
}

void Enemy::onDeath() {
    alive = false;
}