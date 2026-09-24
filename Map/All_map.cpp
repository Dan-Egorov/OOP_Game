#include "All_map.hpp"
#include <algorithm>

Map::Map(GamePlace& place, Player* player, std::vector<Enemy>& enemies)
    : player(player), enemies(enemies), place(place) {}

GamePlace& Map::getPlace() {
    return place;
}
std::pair<int, int> Map::getSize() {
    return place.getSize();
}

Player* Map::findPlayer() {
    return player;
}
const Player* Map::findPlayer() const {
    return player;
}

std::vector<Enemy>& Map::getEnemies() {
    return enemies;
}
const std::vector<Enemy>& Map::getEnemies() const {
    return enemies;
}

std::vector<std::pair<int, int>>& Map::getVisibleWals() {
    return visibleWals;
}
std::vector<Factory>& Map::getFactories() {
    return factories;
}

void Map::addFactory(const Factory& f) {
    factories.push_back(f);
}
void Map::addEnemy(const Enemy& e) {
    enemies.push_back(e);
}

bool Map::botHere(int x, int y) const {
    if (player->getPosition().first == x &&
        player->getPosition().second == y) return true;
    for (const auto& e : enemies)
        if (e.isAlive() && e.getPosition().first == x &&
            e.getPosition().second == y) return true;
    return false;
}

bool Map::walHere(int x, int y) const {
    return !place.isPassable(x, y);
}

bool Map::factoryHere(int x, int y) const {
    for (const auto& f: factories)
        if (f.occupies(x, y)) return true;
    return false;
}

bool Map::aliveEnemyAt(int x, int y) const {
    for (const auto& e: enemies)
        if (e.isAlive() && e.getPosition().first == x &&
            e.getPosition().second == y) return true;
    return false;
}

bool Map::deadEnemyAt(int x, int y) const {
    for (const auto& e : enemies)
        if (!e.isAlive() && e.getPosition().first == x &&
            e.getPosition().second == y) return true;
    return false;
}

Robot* Map::robotAt(int x, int y) {
    if (player->getPosition().first == x &&
        player->getPosition().second == y) return player;
    for (auto& e: enemies)
        if (e.isAlive() && e.getPosition().first  == x &&
            e.getPosition().second == y) return &e;
    return nullptr;
}

const Robot* Map::robotAt(int x, int y) const {
    if (player->getPosition().first == x &&
        player->getPosition().second == y) return player;
    for (const auto& e : enemies)
        if (e.isAlive() && e.getPosition().first  == x &&
            e.getPosition().second == y) return &e;
    return nullptr;
}

void Map::removeDeadEnemyAt(int x, int y) {
    for (auto i =enemies.begin(); i != enemies.end(); i++) {
        if (!i->isAlive() && i->getPosition().first  == x &&  i->getPosition().second == y) {
            enemies.erase(i);
            break;
        }
    }
}