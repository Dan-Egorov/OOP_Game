#pragma once
#include <vector>
#include "../Player/player.hpp"
#include "../Enemy/enemy.hpp"
#include "../GamePlace/place.hpp"
#include "../Factory/factory.hpp"

class Map {
private:
    Player* player;
    std::vector<Enemy>& enemies;
    GamePlace& place;
    std::vector<std::pair<int, int>> visibleWals;
    std::vector<Factory> factories;

public:
    Map(GamePlace& place, Player* player, std::vector<Enemy>& enemies);

    GamePlace& getPlace();
    std::pair<int, int> getSize();

    Player* findPlayer();
    const Player* findPlayer() const;

    std::vector<Enemy>& getEnemies();
    const std::vector<Enemy>& getEnemies() const;

    std::vector<std::pair<int, int>>& getVisibleWals();
    std::vector<Factory>& getFactories();

    void addFactory(const Factory& f);
    void addEnemy(const Enemy& e);

    bool botHere(int x, int y) const;
    bool walHere(int x, int y) const;
    bool factoryHere(int x, int y) const;
    bool aliveEnemyAt(int x, int y) const;
    bool deadEnemyAt(int x, int y) const;

    Robot* robotAt(int x, int y);
    const Robot* robotAt(int x, int y) const;

    void removeDeadEnemyAt(int x, int y);
};