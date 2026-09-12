#pragma once
#include "../Map/All_map.hpp"

class Vriter {
private:
    Map gameMap;
public:
    Vriter(Map map);

    void printMap();
};