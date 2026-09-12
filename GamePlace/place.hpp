#pragma once
#include <iostream>
#include <vector>

typedef struct Pixel {
    int x, y;
    bool pass;
    int difficulty;
    Pixel(int x, int y, bool val = true, int diff = 1) : x(x), y(y), pass(val), difficulty(diff) {}
}Pixel;

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