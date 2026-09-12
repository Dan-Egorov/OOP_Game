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
