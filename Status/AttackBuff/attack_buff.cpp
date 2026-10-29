#include "attack_buff.hpp"
#include "../../Robot/robot.hpp"

AttackBuff::AttackBuff(int turns) : turnsLeft(turns), savedPower(0) {}

StatusType AttackBuff::getType() const {
    return Overload_st;
}

std::string AttackBuff::getName() const {
    return "Attack Buff";
}

void AttackBuff::apply(Robot& bot) {
    savedPower = bot.getPower();
    bot.setPower(bot.getPower() + 5);
}

void AttackBuff::remove(Robot& bot) {
    bot.setPower(savedPower);
}

void AttackBuff::merge(const Status& other) {
    if (auto* s = dynamic_cast<const AttackBuff*>(&other))
        turnsLeft += s->turnsLeft;
}

void AttackBuff::tick(Robot&) {
    turnsLeft--;
}

bool AttackBuff::isExpired() const {
    return turnsLeft < 0;
}