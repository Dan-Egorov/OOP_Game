#include "place.hpp"
#include <vector>
#include <iostream>

#include "../Config/GameConfig.hpp"

GamePlace::GamePlace(int h, int w): size(h, w) {
    if (h > Config::Map::MAX_SIZE || w > Config::Map::MAX_SIZE) {
        throw std::invalid_argument("width or height value is too big");
    }
    if (h < Config::Map::MIN_SIZE || w < Config::Map::MIN_SIZE) {
        throw std::invalid_argument("width or height value is too small");
    }
    for (int i = 0; i < h; i++) {
        place.push_back(std::vector<Pixel>());
        for (int j = 0; j < w; j++) {
            place[i].push_back(Pixel());
        }
    }
}

void GamePlace::print_place() {
    for (int i = 0; i < size.first; i++) {
        for (int j = 0; j < size.second; j++) {
            std::cout << place[i][j].pass << " ";
        }
        std::cout << std::endl;
    }
}

std::pair<int, int> GamePlace::getSize() {
    return size;
}

std::vector<std::vector<Pixel>>& GamePlace::getPlace() {
    return place;
}

int GamePlace::getDifficulty(int row, int col) const {
    return place[row][col].difficulty;
}

bool GamePlace::isPassable(int row, int col) const {
    return place[row][col].pass;
}