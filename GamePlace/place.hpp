#pragma once
#include <iostream>
#include <vector>

struct Pixel {
    bool pass;
    int difficulty;
    Pixel(bool val = true, int diff = 1) : pass(val), difficulty(diff) {}
};

class GamePlace {
private:
    std::pair<int, int> size;
    std::vector<std::vector<Pixel>> place;
public:
    GamePlace(int h, int w);

    std::pair<int, int> getSize();
    std::vector<std::vector<Pixel>>& getPlace();
    int getDifficulty(int row, int col) const;
    bool isPassable(int row, int col) const;

    void print_place();
};