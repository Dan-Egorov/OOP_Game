#include <iostream>
#include <vector>

#include "Player/player.hpp"
#include "Enemy/enemy.hpp"
#include "GamePlace/place.hpp"
#include "Visual/drawer.hpp"
#include "Map/All_map.hpp"
#include "Game/game.hpp"
#include "Factory/factory.hpp"

int main() {
    GamePlace game(10, 20);

    game.getPlace()[4][5].difficulty = 2;
    game.getPlace()[4][6].difficulty = 2;
    game.getPlace()[4][7].difficulty = 2;
    game.getPlace()[7][10].difficulty = 3;
    game.getPlace()[7][11].difficulty = 3;

    for (int i = 2; i < 18; i++) game.getPlace()[2][i].pass = false;
    for (int i = 3; i < 8;  i++) game.getPlace()[i][3].pass = false;

    Player player(10, 20, 10, 10, 1, 3, 6);
    player.setPosition({0, 1});

    std::vector<Enemy> enemies;
    Enemy e1(5, 10, 2, 5, 10, 3, 3);
    e1.setPosition({1, 1});
    enemies.push_back(e1);

    Map map(game, &player, enemies);
    map.addFactory(Factory({8, 17}, 8));

    Game play(map);
    play.run();
    return 0;
}