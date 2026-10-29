#include "health_potion.hpp"
#include "../../Robot/robot.hpp"
#include "../Config/GameConfig.hpp"
#include <iostream>

std::string HealthPotion::getName() const {
    return "Health Potion";
}

void HealthPotion::use(Robot& bot) {
    bot.setHp(bot.getHp() + Config::Items::HEALTH_POTION_HEAL);
    std::cout << "[Item] Used Health Potion: +20 HP\n";
}
