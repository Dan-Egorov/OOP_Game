#pragma once
#include "../Map/All_map.hpp"
#include "../Visual/drawer.hpp"

class Game {
private:
    Map& map;
    int step;
public:
    Game(Map& m);

    void PlayerStep();
    void enemyStep();
    void endSteps();

    bool allEnemiesDead() const;
    bool playerDead() const;
    void run();
};