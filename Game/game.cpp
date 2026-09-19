#include "game.hpp"
#include <iostream>
#include "../MovSystem/moving.hpp"

enum EndState {
    Win,
    Lose
};

Game::Game(Map& m): map(m) {}

void Game::PlayerStep() {
    std::string stp;
    std::cout << "Player: ";
    std::getline(std::cin, stp);
    Robot* player = map.findPlayer();

    int steps = player->getSpeed();
    for (auto step: stp) {
        int new_x = 0;
        int new_y = 0;
        if (steps <= 0) break;

        if (step == 'w') new_x = -1;
        else if (step == 's') new_x = 1;
        else if (step == 'a') new_y = -1;
        else if (step == 'd') new_y = 1;
        Mov::makeMove(map, new_x, new_y, *(player), steps);
    }
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

        int steps = robot.getSpeed();
        if (dx != 0 && Mov::makeMove(map, dx, 0, robot, steps)) continue;
        if (dy != 0 && Mov::makeMove(map, 0, dy, robot, steps)) continue;
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
    for (auto& r : map.getRobots())
        if (r.getType() == ENEMY && r.getHp() > 0) return false;
    return true;
}

bool Game::playerDead() const {
    const Robot* p = map.findPlayer();
    return p && p->getHp() <= 0;
}

void Game::factoryStep() {
    for (auto& f : map.getFactories())
        f.tick(map);
}

void Game::run() {
    Vriter vriter(map);
    bool running = true;
    EndState state = Win;

    while (running) {
        vriter.printMap();

        PlayerStep();
        if (playerDead()) {
            state = Lose;
            running = false;
        }

        if (running) {
            enemyStep();
            if (allEnemiesDead()) {
                state = Win;
                running = false;
            }
        }

        if (running) {
            factoryStep();
            endSteps();
        }
    }

    if (state == Win) {
        std::cout << "All enemies dead!!!" << std::endl;
        std::cout << "You are won!!!!" << std::endl;
    } else {
        std::cout << "You are dead!!!!" << std::endl;
    }
}