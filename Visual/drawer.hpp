#pragma once
#include "../Map/All_map.hpp"
#include <vector>

enum ViewMode {
    STANDARD,
    HIGHLIGHT_ENEMIES,
    HIGHLIGHT_WALLS,
    HIGHLIGHT_STATUS_CELLS
};

class Vriter {
private:
    Map& gameMap;
    std::vector<Enemy*> highlighted;
    std::vector<std::pair<int,int>> greenCells;
    ViewMode mode = STANDARD;
public:
    explicit Vriter(Map& map);

    void setHighlight(const std::vector<Enemy*>& t) { highlighted = t; }
    void clearHighlight() { highlighted.clear(); }
    void setGreenCells(const std::vector<std::pair<int,int>>& c) { greenCells = c; }
    void clearGreenCells() { greenCells.clear(); }

    void nextMode() { mode = static_cast<ViewMode>((mode + 1) % 4); }
    ViewMode getMode() const { return mode; }

    void printMap();
};