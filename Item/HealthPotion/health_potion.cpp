#include "health_potion.hpp"
#include "../../Robot/robot.hpp"
#include <iostream>

std::string HealthPotion::getName() const {
    return "Health Potion";
}

void HealthPotion::use(Robot& bot) {
    bot.setHp(bot.getHp() + 20);
    std::cout << "[Item] Used Health Potion: +20 HP\n";
}
