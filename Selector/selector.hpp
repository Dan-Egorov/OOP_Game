#pragma once
#include <utility>
#include <vector>
#include "../Enemy/enemy.hpp"

class Robot;
class Map;
class Vriter;

namespace Selector {
    std::vector<Enemy*> EnemySelectorInRadius(Map& map, int x_p, int y_p, int radius);

    Enemy* selectEnemyInRange(std::vector<Enemy*>& targets);
}