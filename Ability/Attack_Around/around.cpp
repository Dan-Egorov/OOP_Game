#include "around.hpp"
#include "../Map/All_map.hpp"
#include <iostream>

Around::Around(int damage, int radius, int e) : damage(damage), radius(radius), usedEnergy(e) {}

std::string Around::getName() {
    return "around";
}

int Around::getUsedEnergy() {
    return usedEnergy;
}

AbilityType Around::getType() const {
    return Around_ab;
}

void Around::upgrade() {
    radius += 1;
}

void Around::use(Player &robot, Map &map, Enemy*) {
    if (robot.getEnergy() < usedEnergy) {
        std::cout << "Не хватает энергии" << std::endl;
        return;
    };
    std::pair<int, int> position = robot.getPosition();
    int x = position.first, y = position.second;
    for (int i = x-radius; i <= x+radius; i++) {
        for (int j = y-radius; j <= y+radius; j++) {
            if (i == x && j == y) continue;
            if (!map.aliveEnemyAt(i, j)) continue;

            Robot* enemy = map.robotAt(i, j);
            int new_hp = enemy->getHp() - damage;

            if (new_hp < 0) new_hp = 0;
            enemy->setHp(new_hp);

            if (enemy->getHp() == 0) {
                enemy->onDeath();
                robot.onKill();
            }
        }
    }
    robot.setEnergy(robot.getEnergy() - usedEnergy);
}