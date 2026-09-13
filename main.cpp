#include <iostream>
#include "Robot/robot.hpp"
#include "GamePlace/place.hpp"
#include "Visual/drawer.hpp"
#include "Map/All_map.hpp"
#include "MovSystem/moving.hpp"
#include "Game/game.hpp"
#include "Factory/factory.hpp"

int main() {
    Robot robot(10, 20, 10, 10, 1, PLAYER);
    Robot enemy(5, 10, 2, 5, 10, ENEMY);
    robot.setPosition(std::pair<int, int>(0, 1));
    robot.setVision(6);
    enemy.setPosition(std::pair<int, int>(1, 1));
    GamePlace game(10, 20);

    game.getPlace()[4][5].difficulty = 2;
    game.getPlace()[4][6].difficulty = 2;
    game.getPlace()[4][7].difficulty = 2;

    game.getPlace()[7][10].difficulty = 3;
    game.getPlace()[7][11].difficulty = 3;

    std::vector<Robot> robots;
    robots.push_back(robot);
    robots.push_back(enemy);

    for (int i = 2; i < 18; i++) {
        game.getPlace()[2][i].pass = false;
    }
    for (int i = 3; i < 8; i++) {
        game.getPlace()[i][3].pass = false;
    }

    Map map(game, robots);
    map.addFactory(Factory({8, 17}, 8));

    Game play(map);
    play.run();
    return 0;
}