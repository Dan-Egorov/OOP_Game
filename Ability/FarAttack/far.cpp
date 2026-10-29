#include "../Visual/drawer.hpp"
#include "../Selector/selector.hpp"
#include "../Player/player.hpp"
#include "../Status/Burning/burning.hpp"
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

void Far::use(Robot& robot, Map& map, Enemy* target) {
    if (robot.getEnergy() < usedEnergy) {
        std::cout << "Не хватает энергии" << std::endl;
        return;
    }

    if (target) {
        target->takeDamage(damage);

        if (target->getHp() == 0) {
            robot.onKill();
        }
    }

    robot.addStatus(std::make_shared<Burning>(3, 2));

    robot.setEnergy(robot.getEnergy() - usedEnergy);
}