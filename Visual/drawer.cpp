#include "drawer.hpp"
#include <iostream>
#include <cmath>

Vriter::Vriter(Map& game): gameMap(game) {}

bool in_vision(int i, int j, std::pair<int, int> player_coordinate, Robot &player) {
    return std::abs(i - player_coordinate.first) <= player.getVision() && std::abs(j - player_coordinate.second) <= player.getVision();
}

void Vriter::printMap() {
    Robot* player = gameMap.findPlayer();
    std::pair<int, int> player_coords = std::make_pair(player->getPosition().first, player->getPosition().second);

    for (int i = 0; i < gameMap.getSize().first; i++) {
        for (int j = 0; j < gameMap.getSize().second; j++) {
            if (i == player_coords.first && j == player_coords.second) {
                std::cout << "p" << " ";
            }
            else if (gameMap.factoryHere(i, j)) {
                std::cout << "F" << " ";
            }
            else if (gameMap.botHere(i, j) && in_vision(i, j, player_coords, *player)) {
                std::cout << "e" << " ";
            }
            else if (gameMap.getPlace().getPlace()[i][j].pass == true && in_vision(i, j, player_coords, *player)) {
                int hard = gameMap.getPlace().getDifficulty(i, j);

                if (hard == 1) {
                    std::cout << "." << " ";
                } else if (hard == 2) {
                    std::cout << "'" << " ";
                } else std::cout << ":" << " ";
            }
            else if (gameMap.getPlace().getPlace()[i][j].pass == false && in_vision(i, j, player_coords, *player)) {
                gameMap.getVisibleWals().push_back(std::make_pair(i, j));
                std::cout << "o" << " ";
            } else {
                bool was_wall = false;
                for (auto w : gameMap.getVisibleWals()) {
                    if (i == w.first && j == w.second) {
                        std::cout << "o" << " ";
                        was_wall = true;
                        break;
                    }
                }
                if (!was_wall) std::cout << "?" << " ";
            }
        }
        std::cout << std::endl;
    }
}