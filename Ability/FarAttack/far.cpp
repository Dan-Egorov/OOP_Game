#include "../Visual/drawer.hpp"
#include "../Selector/selector.hpp"
#include "../Player/player.hpp"
#include "far.hpp"

#include <map>

Far::Far(int dam, int rad, int e): damage(dam), radius(rad), usedEnergy(e) {}

std::string Far::getName() {
    return "Far";
}

int Far::getUsedEnergy() {
    return usedEnergy;
}

AbilityType Far::getType() const {
    return Far_ab;
}

void Far::upgrade() {
    damage += 5;
}

void Far::use(Player& robot, Map& map, Enemy* target) {
    if (robot.getEnergy() < usedEnergy) {
        std::cout << "Не хватает энергии" << std::endl;
        return;
    }

    if (target) {
        int new_hp = target->getHp() - damage;
        if (new_hp < 0) new_hp = 0;
        target->setHp(new_hp);

        if (target->getHp() == 0) {
            target->onDeath();
            robot.onKill();
        }
    }

    robot.setEnergy(robot.getEnergy() - usedEnergy);
}