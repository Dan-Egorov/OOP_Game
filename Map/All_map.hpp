#pragma once
#include <vector>
#include "../Robot/robot.hpp"
#include "../GamePlace/place.hpp"
#include "../Factory/factory.hpp"

class Map {
private:
    std::vector<Robot>& robots;
    GamePlace& place;
    std::vector<std::pair<int, int>> visibleWals;
    std::vector<Factory> factories;
public:
    Map(GamePlace& place, std::vector<Robot>& robots);

    GamePlace& getPlace();
    std::pair<int, int> getSize();
    std::vector<Robot>& getRobots();
    std::vector<std::pair<int, int>>& getVisibleWals();

    std::vector<Factory>& getFactories();

    void addFactory(const Factory& f);
    void addRobot(const Robot& r);

    bool botHere(int x, int y);
    bool walHere(int x, int y);
    bool factoryHere(int x, int y) const;

    Robot* robotAt(int x, int y);

    Robot* findPlayer();
};
