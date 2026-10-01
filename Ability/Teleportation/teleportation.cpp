#include "teleportation.hpp"
#include "../Map/All_map.hpp"

Teleportation::Teleportation(int r, int e): range(r), usedEnergy(e) {}

std::string Teleportation::getName() {
    return "Teleport";
}
int Teleportation::getUsedEnergy() {
    return usedEnergy;
}

AbilityType Teleportation::getType() const {
    return Teleport_ab;
}

void Teleportation::upgrade() {
    if (usedEnergy > 3) usedEnergy -= 3;
    else usedEnergy = 1;
}

std::vector<std::pair<int,int>> Teleportation::collectValidCells(Player& player, Map& map) {
    std::vector<std::pair<int,int>> cells;
    std::pair<int,int> user_pos = player.getPosition();
    int px = user_pos.first;
    int py = user_pos.second;

    for (int dr = -range; dr <= range; ++dr) {
        for (int dc = -range; dc <= range; ++dc) {
            if (dr == 0 && dc == 0) continue;
            if ((dr*dr + dc*dc) > range*range) continue;

            int r = px + dr;
            int c = py + dc;

            if (r < 0 || c < 0) continue;
            if (r >= map.getSize().first || c >= map.getSize().second) continue;

            if (!map.getPlace().isPassable(r, c)) continue;

            if (map.robotAt(r, c) != nullptr) continue;

            if (map.deadEnemyAt(r, c)) continue;
            if (map.factoryHere(r, c)) continue;

            cells.push_back({r, c});
        }
    }
    return cells;
}

void Teleportation::applyTeleport(Player& player, std::pair<int,int> cell) {
    if (player.getEnergy() < usedEnergy) {
        std::cout << "Не хватает энергии\n";
        return;
    }
    player.setEnergy(player.getEnergy() - usedEnergy);
    player.setPosition(cell);
}