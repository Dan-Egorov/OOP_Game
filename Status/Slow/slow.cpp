#include "slow.hpp"
#include "../Robot/robot.hpp"

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