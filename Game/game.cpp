#include "game.hpp"
#include <iostream>
#include "../MovSystem/moving.hpp"

Game::Game(Map& m): map(m) {}

void Game::PlayerStep() {
    std::string stp;
    std::cout << "Player: ";
    std::cin >> stp;
    Robot* player = map.findPlayer();

    int new_x = 0;
    int new_y = 0;

    if (stp == "w") new_x = -1;
    if (stp == "s") new_x = 1;
    if (stp == "a") new_y = -1;
    if (stp == "d") new_y = 1;

    Mov::makeMove(map, new_x, new_y, *(player));
}

void Game::enemyStep() {
    Robot* player = map.findPlayer();
    if (!player) return;

    for (auto& robot : map.getRobots()) {
        if (robot.getType() != ENEMY) continue;
        if (robot.getHp() <= 0) continue;

        int dx = (player->getPosition().first  > robot.getPosition().first)
               - (player->getPosition().first  < robot.getPosition().first);
        int dy = (player->getPosition().second > robot.getPosition().second)
               - (player->getPosition().second < robot.getPosition().second);

        if (dx != 0 && Mov::makeMove(map, dx, 0, robot)) continue;
        if (dy != 0 && Mov::makeMove(map, 0, dy, robot)) continue;
    }
}

void Game::endSteps() {
    for (auto& robot : map.getRobots()) {
        if (robot.getHp() <= 0) continue;
        robot.setEnergy(robot.getEnergy() + 5);
        robot.setHp(robot.getHp() + 1);
    }
}

bool Game::allEnemiesDead() const {
    for (const auto& r : map.getRobots())
        if (r.getType() == ENEMY && r.getHp() > 0) return false;
    return true;
}

bool Game::playerDead() const {
    const Robot* p = map.findPlayer();
    return p && p->getHp() <= 0;
}

void Game::run() {
    Vriter vriter(map);

    while (true) {
        vriter.printMap();

        PlayerStep();
        if (playerDead()) {
            std::cout << "You are dead!!!!" << std::endl;
            return;
        }

        enemyStep();
        if (allEnemiesDead()) {
            std::cout << "All enemies dead!!!" << std::endl;
            std::cout << "You are won!!!!" << std::endl;
            return;
        }

        endSteps();
    }
}