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
    std::pair<int, int> chooseNear(std::vector<std::pair<int,int>> cells,
        std::pair<int,int> player_position);
    void PlayerStep(Vriter& vriter);
    void enemyStep();
    void endSteps();

    bool allEnemiesDead() const;
    bool playerDead() const;
    void factoryStep();
    void run();
};