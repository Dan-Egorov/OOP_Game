#include "drawer.hpp"
#include <iostream>
#include <cmath>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define ORANGE "\033[38;5;208m"
#define GREEN_PLAYER "\033[94m"
#define RESET "\033[0m"

Vriter::Vriter(Map& game) : gameMap(game) {}

bool in_vision(int i, int j, std::pair<int,int> pc, Robot& p) {
    return std::abs(i - pc.first)  <= p.getVision() &&
           std::abs(j - pc.second) <= p.getVision();
}

void Vriter::printMap() {
    Player* player = gameMap.findPlayer();
    auto pc = player->getPosition();

    for (int i = 0; i < gameMap.getSize().first; i++) {
        for (int j = 0; j < gameMap.getSize().second; j++) {

            bool isGreen = false;
            for (auto& c: greenCells) {
                if (c.first == i && c.second == j) {
                    isGreen = true;
                    break;
                }
            }
            if (isGreen) {
                std::cout << GREEN << "* " << RESET;
                continue;
            }

            int idx = -1;
            for (int k = 0; k < highlighted.size(); k++) {
                std::pair<int, int> p = highlighted[k]->getPosition();
                if (p.first == i && p.second == j) {
                    idx = k;
                    break;
                }
            }
            if (idx >= 0) {
                std::cout << RED << idx << RESET << " ";
            }
            else if (i == pc.first && j == pc.second) {
                if (player->getIsBurning()) {
                    std::cout << ORANGE << "p " << RESET;
                } else if (player->getSpeed() == 0)
                    std::cout << GREEN_PLAYER << "p " << RESET;
                else
                    std::cout << "p ";
            }
            else if (gameMap.factoryHere(i, j)) {
                std::cout << "F ";
            }
            else if (gameMap.aliveEnemyAt(i, j) && in_vision(i, j, pc, *player)) {
                if (gameMap.robotAt(i, j)->getIsBurning())
                    std::cout << ORANGE << "e " << RESET;
                else
                    std::cout << "e ";
            }
            else if (gameMap.deadEnemyAt(i, j) && in_vision(i, j, pc, *player)) {
                std::cout << "x ";
            }
            else if (gameMap.getPlace().isPassable(i, j) && in_vision(i, j, pc, *player)) {
                int hard = gameMap.getPlace().getDifficulty(i, j);
                if (hard == 1)      std::cout << ". ";
                else if (hard == 2) std::cout << "' ";
                else                std::cout << ": ";
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
        std::cout << "\n";
    }
    std::cout.flush();
}