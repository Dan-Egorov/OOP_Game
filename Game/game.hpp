#pragma once
#include "../Map/All_map.hpp"
#include "../Visual/drawer.hpp"

class Game {
private:
    Map& map;
    int step;
public:
    Game(Map& m);

    void handleRankUpChoice(Player& player);
    void chooseNewAbility(Player& player);
    void chooseUpgradeAbility(Player& player);
    void PlayerStep(Vriter& vriter);
    void enemyStep();
    void endSteps();

    bool allEnemiesDead() const;
    bool playerDead() const;
    void factoryStep();
    void run();
};