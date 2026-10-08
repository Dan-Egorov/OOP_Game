#include "overload.hpp"

#include "../../Robot/robot.hpp"

StatusType Overload::getType() const {
    return Overload_st;
}

std::string Overload::getName() const {
    return "Overload";
}

void Overload::apply(Robot &bot) {
    bot.setOverloaded(true);
}

void Overload::remove(Robot &bot) {
    bot.setOverloaded(false);
}

void Overload::merge(const Status &other) {}
void Overload::tick(Robot &bot) {}
bool Overload::isExpired() const {return false;}
