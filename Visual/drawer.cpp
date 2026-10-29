#include "drawer.hpp"
#include <iostream>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define PURPLE "\033[35m"
#define ORANGE "\033[38;5;208m"
#define STOP_PLAYER "\033[94m"
#define BROWN "\033[33m"
#define DARK_BLUE "\033[34m"
#define YELLOW_PLAYER "\033[93m"
#define TURQUOISE "\033[38;5;45m"
#define TOMATO "\033[38;5;202m"
#define WHITE "\033[97m"
#define GRAY "\033[90m"
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

            bool hasStatus = !gameMap.getPlace().getPlace()[i][j].pixelStates.empty();

            if (mode == HIGHLIGHT_WALLS && !gameMap.getPlace().isPassable(i, j)) {
                std::cout << RED << "o " << RESET;
                continue;
            }
            if (mode == HIGHLIGHT_STATUS_CELLS && hasStatus) {
                std::cout << RED << "* " << RESET;
                continue;
            }

            if (mode == HIGHLIGHT_ENEMIES && gameMap.aliveEnemyAt(i, j)) {
                std::cout << RED << "! " << RESET;
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
                if (player->getIsBurning())
                    std::cout << ORANGE << "p " << RESET;
                else if (player->getSpeed() == 0)
                    std::cout << STOP_PLAYER << "p " << RESET;
                else if (player->hasStatus(Shield_st))
                    std::cout << PURPLE << "p " << RESET;
                else if (player->isOverloaded())
                    std::cout << YELLOW_PLAYER << "p " << RESET;
                else
                    std::cout << "p ";
            }
            else if (gameMap.factoryHere(i, j)) {
                std::cout << "F ";
            }
            else if (gameMap.aliveEnemyAt(i, j) && in_vision(i, j, pc, *player)) {
                if (gameMap.robotAt(i, j)->getIsBurning())
                    std::cout << ORANGE << "z " << RESET;
                else if (gameMap.robotAt(i, j)->getSpeed() == 0)
                    std::cout << STOP_PLAYER << "z " << RESET;
                else if (gameMap.robotAt(i, j)->hasStatus(Shield_st))
                    std::cout << PURPLE << "z " << RESET;
                else if (gameMap.robotAt(i, j)->hasAbility(Teleport_ab))
                    std::cout << DARK_BLUE << "z " << RESET;
                else if (gameMap.robotAt(i, j)->hasAbility(Heal_ab))
                    std::cout << TURQUOISE << "z " << RESET;
                else
                    std::cout << "z ";
            }
            else if (gameMap.deadEnemyAt(i, j) && in_vision(i, j, pc, *player)) {
                std::cout << WHITE << "x " << RESET;
            }
            else if (gameMap.getPlace().isPassable(i, j) && in_vision(i, j, pc, *player)) {
                int hard = gameMap.getPlace().getDifficulty(i, j);
                if (hard == 1)      std::cout  << ". ";
                else if (hard == 2) std::cout << GRAY << "' " << RESET;
                else                std::cout << GRAY << ": " << RESET;
            }
            else if (!gameMap.getPlace().isPassable(i, j) && in_vision(i, j, pc, *player)) {
                gameMap.getVisibleWals().push_back({i, j});
                std::cout << BROWN << "o " << RESET;
            }
            else {
                bool was_wall = false;
                for (auto w : gameMap.getVisibleWals()) {
                    if (i == w.first && j == w.second) {
                        std::cout << BROWN << "o " << RESET;
                        was_wall = true;
                        break;
                    }
                }
                if (!was_wall) std::cout << "? ";
            }
        }
        std::cout << "\n";
    }
    std::cout.flush();
}