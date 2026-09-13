#include "factory.hpp"
#include "../Robot/robot.hpp"
#include "../Map/All_map.hpp"
#include <vector>

Factory::Factory(std::pair<int, int> pos, int period)
    : position(pos), period(period > 0 ? period : 1), counter(0) {}

std::pair<int, int> Factory::getPosition() const {
    return position;
}

int Factory::getPeriod() const {
    return period;
}

int Factory::getCounter() const {
    return counter;
}

bool Factory::occupies(int row, int col) const {
    return row >= position.first && row <= position.first + 1 && col >= position.second && col <= position.second + 1;
}

bool Factory::tick(Map& map) {
    counter++;
    if (counter < period) return false;
    counter = 0;

    for (int dr = -1; dr <= 2; dr++) {
        for (int dc = -1; dc <= 2; dc++) {
            int r = position.first  + dr;
            int c = position.second + dc;

            if (occupies(r, c)) continue;

            if (r < 0 || c < 0) continue;
            if (r >= map.getSize().first || c >= map.getSize().second) continue;

            if (!map.getPlace().isPassable(r, c)) continue;

            if (map.robotAt(r, c) != nullptr) continue;

            Robot enemy(5, 10, 2, 2, 5, ENEMY);
            enemy.setPosition(std::make_pair(r, c));
            enemy.setSpeed(3);
            map.addRobot(enemy);
            return true;
        }
    }
    return false;
}