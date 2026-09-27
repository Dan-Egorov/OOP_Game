#pragma once
#include "../Map/All_map.hpp"
#include <vector>

class Vriter {
private:
    Map& gameMap;
    std::vector<Enemy*> highlighted;
    std::vector<std::pair<int,int>> greenCells;
public:
    explicit Vriter(Map& map);

    void setHighlight(const std::vector<Enemy*>& t) { highlighted = t; }
    void clearHighlight() { highlighted.clear(); }

    void setGreenCells(const std::vector<std::pair<int,int>>& c) { greenCells = c; }
    void clearGreenCells() { greenCells.clear(); }

    void printMap();
};