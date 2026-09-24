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

    Player* player = map.findPlayer();
    if (!player) return;

    int steps = player->getSpeed();
    for (char step : stp) {
        if (steps <= 0) break;
        int dx = 0, dy = 0;
        if (step == 'w') dx = -1;
        else if (step == 's') dx = 1;
        else if (step == 'a') dy = -1;
        else if (step == 'd') dy = 1;
        Mov::makeMove(map, dx, dy, *player, steps);
    }
}

void Game::enemyStep() {
    Player* player = map.findPlayer();
    if (!player) return;

    for (auto& enemy : map.getEnemies()) {
        if (!enemy.isAlive()) continue;

        int dx = (player->getPosition().first  > enemy.getPosition().first)
               - (player->getPosition().first  < enemy.getPosition().first);
        int dy = (player->getPosition().second > enemy.getPosition().second)
               - (player->getPosition().second < enemy.getPosition().second);

        int steps = enemy.getSpeed();
        if (dx != 0 && Mov::makeMove(map, dx, 0, enemy, steps)) continue;
        if (dy != 0 && Mov::makeMove(map, 0, dy, enemy, steps)) continue;
    }
}

void Game::endSteps() {
    Player* p = map.findPlayer();
    if (p->getHp() > 0) {
        p->setEnergy(p->getEnergy() + 5);
        p->setHp(p->getHp() + 1);
    }
    for (auto& enemy : map.getEnemies()) {
        if (!enemy.isAlive()) continue;
        enemy.setEnergy(enemy.getEnergy() + 5);
        enemy.setHp(enemy.getHp() + 1);
    }
}

bool Game::allEnemiesDead() const {
    for (const auto& e: map.getEnemies())
        if (e.isAlive()) return false;
    return true;
}

bool Game::playerDead() const {
    const Player* p = map.findPlayer();
    return p && p->getHp() <= 0;
}

void Game::factoryStep() {
    for (auto& f: map.getFactories())
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