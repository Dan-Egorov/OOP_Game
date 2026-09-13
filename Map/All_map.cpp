#include "All_map.hpp"

Map::Map(GamePlace& place, std::vector<Robot>& robots): place(place), robots(robots) {}

GamePlace& Map::getPlace() {
    return place;
}

std::pair<int, int> Map::getSize() {
    return place.getSize();
}

std::vector<Robot>& Map::getRobots() {
    return robots;
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

void Map::addRobot(const Robot& r) {
    robots.push_back(r);
}

bool Map::botHere(int x, int y) {
    for (auto robot: robots) {
        if (robot.getPosition().first == x && robot.getPosition().second == y) {
            return true;
        }
    }
    return false;
}

bool Map::walHere(int x, int y) {
    if (place.getPlace()[x][y].pass == false) {
        return true;
    }
    return false;
}

bool Map::factoryHere(int x, int y) const {
    for (auto& f: factories)
        if (f.occupies(x, y)) return true;
    return false;
}

Robot* Map::robotAt(int x, int y) {
    for (auto& robot: robots) {
        if (robot.getPosition().first == x && robot.getPosition().second == y) {
            return &robot;
        }
    }
    return nullptr;
}

Robot* Map::findPlayer() {
    for (auto& robot: robots) {
        if (robot.getType() == PLAYER) {
            return &robot;
        }
    }
    return nullptr;
}
