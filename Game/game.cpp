#include "game.hpp"
#include <iostream>
#include "../MovSystem/moving.hpp"
#include "../FarAttack/far.hpp"
#include "../Attack_Around/around.hpp"
#include "../Heal/heal.hpp"
#include "../Selector/selector.hpp"
#include "../Interface/Teleportation/teleportation.hpp"

enum EndState {
    Win,
    Lose
};

Game::Game(Map& m): map(m) {}

void Game::PlayerStep(Vriter& vriter) {
    std::cout << "Player (w/a/s/d, e = способность): ";
    std::string stp;
    std::getline(std::cin, stp);

    Player* player = map.findPlayer();
    if (!player) return;

    int steps = player->getSpeed();

    for (char step : stp) {
        if (step == 'w' || step == 's' || step == 'a' || step == 'd') {
            if (steps <= 0) break;
            int dx = 0, dy = 0;
            if (step == 'w') dx = -1;
            else if (step == 's') dx = 1;
            else if (step == 'a') dy = -1;
            else if (step == 'd') dy = 1;
            Mov::makeMove(map, dx, dy, *player, steps);
        }
        else if (step == 'e') {
            std::vector<AbilityType> abilityTypes = player->getAbilities();
            for (int i = 0; i < abilityTypes.size(); i++) {
                if (abilityTypes[i] == Around_ab)
                    std::cout << i << ") " << "Attak Around" << std::endl;
                else if (abilityTypes[i] == Heal_ab)
                    std::cout << i << ") " << "Heal" << std::endl;
                else if (abilityTypes[i] == Far_ab)
                    std::cout << i << ") " << "Far" << std::endl;
                else if (abilityTypes[i] == Teleport_ab)
                    std::cout << i << ") Teleport\n";
            }
            std::string choose;


            std::cout << "Choose your ability: ";
            std::getline(std::cin, choose);

            int index = -1;
            try {
                index = std::stoi(choose);
            } catch (...) {
                return;
            }

            if (index < 0 || index >= abilityTypes.size()) {
                std::cout << "Choose error!" << std::endl;
            } else if (!abilityTypes.empty()) {
                if (abilityTypes[index] == Around_ab) {
                    Around around(10, 1);
                    around.use(*player, map);
                } else if (abilityTypes[index] == Heal_ab) {
                    Heal heal(10, 1);
                    heal.use(*player, map);
                } else if (abilityTypes[index] == Far_ab) {
                    Far far(10, 3, 1);
                    int x_p = player->getPosition().first;
                    int y_p = player->getPosition().second;

                    std::vector<Enemy*> enemies = Selector::EnemySelectorInRadius(map, x_p, y_p, 3);

                    vriter.setHighlight(enemies);
                    vriter.printMap();

                    Enemy* enemy = Selector::selectEnemyInRange(enemies);

                    far.use(*player, map, enemy);
                    vriter.clearHighlight();
                } else if (abilityTypes[index] == Teleport_ab) {
                    Teleportation tp(5, 1);

                    std::vector<std::pair<int, int>> cells = tp.collectValidCells(*player, map);
                    if (cells.empty()) {
                        std::cout << "Нет доступных клеток\n";
                        break;
                    }

                    vriter.setGreenCells(cells);
                    vriter.printMap();

                    std::pair<int,int> user_pos = player->getPosition();
                    int px = user_pos.first;
                    int py = user_pos.second;

                    std::cout << "Смещение (drow dcol), например '0 -3': ";
                    std::vector<int> nums;
                    std::string stroke;
                    std::getline(std::cin, stroke);
                    std::string curr_num;

                    for (auto& c : stroke) {
                        if (c == ' ') {
                            try {
                                nums.push_back(std::stoi(curr_num));
                                curr_num.clear();
                            } catch (...) {
                                vriter.clearGreenCells();
                                return;
                            }
                        } else {
                            curr_num += c;
                        }
                    }

                    try {
                        nums.push_back(std::stoi(curr_num));
                        curr_num.clear();
                    } catch (...) {
                        vriter.clearGreenCells();
                        return;
                    }

                    int targetRow = px + nums[0];
                    int targetCol = py + nums[1];

                    bool valid = false;
                    for (auto& c: cells) {
                        if (c.first == targetRow && c.second == targetCol) {
                            valid = true;
                            break;
                        }
                    }

                    vriter.clearGreenCells();

                    if (!valid) {
                        std::cout << "Нельзя туда телепортироваться\n";
                        break;
                    }

                    tp.applyTeleport(*player, {targetRow, targetCol});
                }
            }
        }
    }
}

void Game::enemyStep() {
    Player* player = map.findPlayer();
    if (!player) return;

    for (auto& enemy : map.getEnemies()) {
        if (!enemy.isAlive()) continue;

        int dx = (player->getPosition().first  > enemy.getPosition().first)
               - (player->getPosition().first  < enemy.getPosition().first);
        int dy = (player->getPosition().second > enemy.getPosition().second)
               - (player->getPosition().second < enemy.getPosition().second);

        int steps = enemy.getSpeed();
        if (dx != 0 && Mov::makeMove(map, dx, 0, enemy, steps)) continue;
        if (dy != 0 && Mov::makeMove(map, 0, dy, enemy, steps)) continue;
    }
}

void Game::endSteps() {
    Player* p = map.findPlayer();
    if (p->getHp() > 0) {
        p->setEnergy(p->getEnergy() + 5);
        p->setHp(p->getHp() + 1);
    }
    for (auto& enemy : map.getEnemies()) {
        if (!enemy.isAlive()) continue;
        enemy.setEnergy(enemy.getEnergy() + 5);
        enemy.setHp(enemy.getHp() + 1);
    }
}

bool Game::allEnemiesDead() const {
    for (const auto& e: map.getEnemies())
        if (e.isAlive()) return false;
    return true;
}

bool Game::playerDead() const {
    const Player* p = map.findPlayer();
    return p && p->getHp() <= 0;
}

void Game::factoryStep() {
    for (auto& f: map.getFactories())
        f.tick(map);
}

void Game::run() {
    Vriter vriter(map);
    bool running = true;
    EndState state = Win;

    while (running) {
        vriter.printMap();
        PlayerStep(vriter);

        if (playerDead()) {
            state = Lose;
            running = false;
        }

        if (running) {
            enemyStep();
            if (allEnemiesDead()) {
                state = Win;
                running = false;
            }
        }

        if (running) {
            factoryStep();
            endSteps();
        }
    }

    if (state == Win) {
        std::cout << "All enemies dead!!!" << std::endl;
        std::cout << "You are won!!!!" << std::endl;
    } else {
        std::cout << "You are dead!!!!" << std::endl;
    }
}