#include "burning.hpp"

#include "../../Robot/robot.hpp"

Burning::Burning(int turns, int dam): turnsLeft(turns), damage(dam) {}

StatusType Burning::getType() const {
    return Burning_st;
}

std::string Burning::getName() const {
    return "Burning";
}

void Burning::apply(Robot& bot) {
    bot.setIsBurning(true);
}
void Burning::remove(Robot &bot) {
    bot.setIsBurning(false);
}

void Burning::merge(const Status &other) {
    if (auto* s = dynamic_cast<const Burning*>(&other))
        turnsLeft += s->turnsLeft;
}

void Burning::tick(Robot &bot) {
    turnsLeft--;
    int newHp = bot.getHp() - damage;
    bot.setHp(newHp);
    if (newHp <= 0) {
        newHp = 0;
        bot.onDeath();
    }
}

bool Burning::isExpired() const {
    return turnsLeft <= 0;
}
