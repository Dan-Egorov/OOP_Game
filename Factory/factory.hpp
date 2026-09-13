#pragma once
#include <utility>

class Map;

class Factory {
private:
    std::pair<int, int> position;
    int period;
    int counter;
public:
    Factory(std::pair<int, int> pos, int period);

    std::pair<int, int> getPosition() const;
    int getPeriod() const;
    int getCounter() const;

    bool occupies(int row, int col) const;

    bool tick(Map& map);
};