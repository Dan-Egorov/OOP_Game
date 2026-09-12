#include "drawer.hpp"
#include <iostream>

Vriter::Vriter(Map game): gameMap(game) {}

void Vriter::printMap() {
    for (int i = 0; i < gameMap.getSize().first; i++) {
        for (int j = 0; j < gameMap.getSize().second; j++) {
            if (gameMap.botHere(i, j)) {
                if (gameMap.robotAt(i, j)->getType() == PLAYER) {
                    std::cout << "p" << " ";
                }
                else std::cout << "e" << " ";
            }
            else if (gameMap.getPlace().getPlace()[i][j].pass == true) {
                int hard = gameMap.getPlace().getDifficulty(i, j);

                if (hard == 1) {
                    std::cout << "-" << " ";
                } else if (hard == 2) {
                    std::cout << "'" << " ";
                } else std::cout << ":" << " ";
            }
            else if (gameMap.getPlace().getPlace()[i][j].pass == false) {
                std::cout << "o" << " ";
            }
        }
        std::cout << std::endl;
    }
}