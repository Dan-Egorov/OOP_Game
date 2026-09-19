#include "moving.hpp"

bool Mov::makeMove(Map& map, int dx, int dy, Robot& robot, int& budget) {
    if (dx == 0 && dy == 0) return false;

    bool acted = false;

    int newRow = robot.getPosition().first  + dx;
    int newCol = robot.getPosition().second + dy;

    if (newRow < 0 || newCol < 0) return false;
    if (newRow >= map.getSize().first || newCol >= map.getSize().second) return false;

    if (map.walHere(newRow, newCol)) return false;

    int cost = map.getPlace().getDifficulty(newRow-dx, newCol-dy);

    Robot* other = map.robotAt(newRow, newCol);
    if (other != nullptr && other != &robot) {
        robot.botAction(*other);
        return true;
    }

    robot.setPosition(std::make_pair(newRow, newCol));
    budget -= cost;
    acted = true;

    return acted;
}