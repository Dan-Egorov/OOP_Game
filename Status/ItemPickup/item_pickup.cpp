#include "item_pickup.hpp"
#include "../../Robot/robot.hpp"
#include "../../Item/HealthPotion/health_potion.hpp"
#include "../../Item/EnergyPotion/energy_potion.hpp"
#include "../../Item/AttackBoost/attack_boost.hpp"
#include <iostream>

void ItemPickup::apply(Robot& bot) {
    if (bot.getType() != PLAYER) return;

    int r = rand() % 3;
    std::shared_ptr<Item> newItem;
    if (r == 0) newItem = std::make_shared<HealthPotion>();
    else if (r == 1) newItem = std::make_shared<EnergyPotion>();
    else newItem = std::make_shared<AttackBoost>();

    bot.receiveItem(newItem);
    std::cout << "\n[!] Found item: " << newItem->getName() << "!\n";
}

bool ItemPickup::isExpired() const {
    return true;
}