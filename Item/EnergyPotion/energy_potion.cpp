#include "energy_potion.hpp"
#include "../../Robot/robot.hpp"
#include <iostream>

std::string EnergyPotion::getName() const {
    return "Energy Potion";
}

void EnergyPotion::use(Robot& bot) {
    bot.setEnergy(bot.getEnergy() + 15);
    std::cout << "Used Energy Potion: +15 Energy\n";
}