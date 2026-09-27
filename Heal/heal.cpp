#include "heal.hpp"
#include <iostream>

#include "../Player/player.hpp"

Heal::Heal(int hp, int e): newHp(hp), usedEnergy(e) {}

int Heal::getUsedEnergy() {
    return usedEnergy;
}

std::string Heal::getName() {
    return "Heal";
}

void Heal::use(Player &robot, Map &map, Enemy*) {
    if (robot.getEnergy() < usedEnergy) {
        std::cout << "Не хватает энергии" << std::endl;
        return;
    }
    int new_hp = robot.getHp() + newHp;
    robot.setHp(new_hp);

    robot.setEnergy(robot.getEnergy() - usedEnergy);
}