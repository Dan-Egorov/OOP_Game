#include "shield.hpp"
#include <algorithm>
#include "../../Robot/robot.hpp"

Shield::Shield(int amount): hpLeft(amount) {}

StatusType Shield::getType() const {
    return Shield_st;
}

std::string Shield::getName() const {
    return "Shield";
}

void Shield::apply(Robot&) {}

void Shield::remove(Robot&) {}

void Shield::tick(Robot&) {}

void Shield::merge(const Status& other) {
     auto* s = dynamic_cast<const Shield*>(&other);
    hpLeft += s->hpLeft;
}

int Shield::absorb(int incoming) {
    int blocked = std::min(incoming, hpLeft);
    hpLeft -= blocked;
    return incoming - blocked;
}

bool Shield::isExpired() const {
    return hpLeft <= 0;
}
