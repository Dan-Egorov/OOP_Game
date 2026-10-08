#include "slow.hpp"
#include "../Robot/robot.hpp"

StatusType Slow::getType() const {
    return Slow_st;
}

std::string Slow::getName() const {
    return "Slow";
}

void Slow::apply(Robot& bot) {
    savedSpeed = bot.getSpeed();
    bot.setSpeed(0);
}

void Slow::remove(Robot& bot) {
    bot.setSpeed(savedSpeed);
}

void Slow::merge(const Status& other) {
    if (auto* s = dynamic_cast<const Slow*>(&other))
        turnsLeft += s->turnsLeft;
}

void Slow::tick(Robot&) {
    turnsLeft--;
}

bool Slow::isExpired() const {
    return turnsLeft < 0;
}