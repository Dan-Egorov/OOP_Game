#include "heal.hpp"
#include <iostream>
#include "../Player/player.hpp"
#include "../Status/Shield/shield.hpp"

Heal::Heal(int hp, int e): newHp(hp), usedEnergy(e) {}

int Heal::getUsedEnergy() {
    return usedEnergy;
}

std::string Heal::getName() {
    return "Heal";
}

AbilityType Heal::getType() const {
    return Heal_ab;
}

void Heal::upgrade() {
    newHp += 5;
}

void Heal::use(Robot &robot, Map &map, Enemy*) {
    if (robot.getEnergy() < usedEnergy) {
        std::cout << "Not enough energy" << std::endl;
        return;
    }
    int new_hp = robot.getHp() + newHp;

    if (new_hp >= robot.getHpMax()) {
        int over = new_hp - robot.getHpMax();
        robot.addStatus(std::make_shared<Shield>(over));
    }

    robot.setHp(new_hp);

    robot.setEnergy(robot.getEnergy() - usedEnergy);
}