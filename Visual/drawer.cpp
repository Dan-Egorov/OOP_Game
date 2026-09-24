#include "drawer.hpp"
#include <iostream>
#include <cmath>

Vriter::Vriter(Map& game): gameMap(game) {}

bool in_vision(int i, int j, std::pair<int, int> pc, Robot& player) {
    return std::abs(i - pc.first)  <= player.getVision() &&
           std::abs(j - pc.second) <= player.getVision();
}

void Vriter::printMap() {
    Player* player = gameMap.findPlayer();
    std::pair<int, int> pc = player->getPosition();

    for (int i = 0; i < gameMap.getSize().first; i++) {
        for (int j = 0; j < gameMap.getSize().second; j++) {
            if (i == pc.first && j == pc.second) {
                std::cout << "p ";
            }

            else if (gameMap.factoryHere(i, j)) {
                std::cout << "F ";
            }

            else if (gameMap.aliveEnemyAt(i, j) && in_vision(i, j, pc, *player)) {
                std::cout << "e ";
            }

            else if (gameMap.deadEnemyAt(i, j) && in_vision(i, j, pc, *player)) {
                std::cout << "x ";
            }

            else if (gameMap.getPlace().isPassable(i, j) && in_vision(i, j, pc, *player)) {
                int hard = gameMap.getPlace().getDifficulty(i, j);
                if (hard == 1)      std::cout << ". ";
                else if (hard == 2) std::cout << "' ";
                else if (hard == 3) std::cout << ": ";

            }
            else if (!gameMap.getPlace().isPassable(i, j) && in_vision(i, j, pc, *player)) {
                gameMap.getVisibleWals().push_back({i, j});
                std::cout << "o ";
            }

            else {
                bool was_wall = false;
                for (auto w : gameMap.getVisibleWals()) {
                    if (i == w.first && j == w.second) {
                        std::cout << "o "; was_wall = true; break;
                    }
                }
                if (!was_wall) std::cout << "? ";
            }
        }
        std::cout << std::endl;
    }
}