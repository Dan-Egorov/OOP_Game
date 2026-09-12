#include "moving.hpp"

bool Mov::makeMove(Map& map, int dx, int dy, Robot& robot) {
    if (dx == 0 && dy == 0) return false;

    int budget = robot.getSpeed();
    bool acted = false;

    while (budget > 0) {
        int newRow = robot.getPosition().first  + dx;
        int newCol = robot.getPosition().second + dy;

        if (newRow < 0 || newCol < 0) break;
        if (newRow >= map.getSize().first || newCol >= map.getSize().second) break;

        if (map.walHere(newRow, newCol)) break;

        int cost = map.getPlace().getDifficulty(newRow, newCol);
        if (cost > budget) break;

        Robot* other = map.robotAt(newRow, newCol);
        if (other != nullptr && other != &robot) {
            robot.botAction(*other);
            return true;
        }

        robot.setPosition(std::make_pair(newRow, newCol));
        budget -= cost;
        acted = true;
    }

    return acted;
}