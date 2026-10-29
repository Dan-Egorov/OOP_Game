#include "energy_potion.hpp"
#include "../../Robot/robot.hpp"
#include "../Config/GameConfig.hpp"
#include <iostream>

std::string EnergyPotion::getName() const {
    return "Energy Potion";
}

void EnergyPotion::use(Robot& bot) {
    bot.setEnergy(bot.getEnergy() + Config::Items::ENERGY_POTION_RESTORE);
    std::cout << "Used Energy Potion: +15 Energy\n";
}