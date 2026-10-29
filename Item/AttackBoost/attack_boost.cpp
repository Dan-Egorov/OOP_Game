#include "attack_boost.hpp"
#include "../../Robot/robot.hpp"
#include "../../Status/AttackBuff/attack_buff.hpp"
#include "../Config/GameConfig.hpp"
#include <iostream>
#include <memory>

std::string AttackBoost::getName() const {
    return "Attack Boost";
}

void AttackBoost::use(Robot& bot) {
    bot.addStatus(std::make_shared<AttackBuff>(Config::Items::ATTACK_BOOST_TURNS));
    std::cout << "[Item] Used Attack Boost: +5 Power for 3 turns\n";
}