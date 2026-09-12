#pragma once
#include <vector>
#include "../Robot/robot.hpp"
#include "../GamePlace/place.hpp"

class Map {
private:
    std::vector<Robot>& robots;
    GamePlace& place;
public:
    Map(GamePlace& place, std::vector<Robot>& robots);

    GamePlace& getPlace();
    std::pair<int, int> getSize();
    std::vector<Robot>& getRobots();

    bool botHere(int x, int y);
    bool walHere(int x, int y);

    Robot* robotAt(int x, int y);

    Robot* findPlayer();
};
