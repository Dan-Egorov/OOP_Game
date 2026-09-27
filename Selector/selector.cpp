#include "selector.hpp"
#include "../Map/All_map.hpp"
#include "../Visual/drawer.hpp"
#include <iostream>
#include <string>

namespace Selector {

    std::vector<Enemy*> EnemySelectorInRadius(Map& map, int x_p, int y_p, int radius) {
        std::vector<Enemy*> targets;
        for (Enemy& e : map.getEnemies()) {
            if (std::abs(e.getPosition().first - x_p) <= radius
                && std::abs(e.getPosition().second - y_p) <= radius) {
                if (e.isAlive())
                    targets.push_back(&e);
            }
        }
        return targets;
    }

    Enemy* selectEnemyInRange(std::vector<Enemy*>& targets) {
        if (targets.empty()) {
            std::cout << "Нет целей в радиусе.\n";
            return nullptr;
        }
        if (targets.size() > 10) targets.resize(10);

        std::cout << "Цель 0-" << targets.size() - 1 << " (q - отмена): ";
        std::string line;
        std::getline(std::cin, line);

        if (line == "q" || line.empty()) return nullptr;

        int idx;
        try {
            idx = std::stoi(line);
        }
        catch (...) {
            return nullptr;
        }

        if (idx < 0 || idx >= targets.size())
            return nullptr;

        return targets[idx];
    }

}