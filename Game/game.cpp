#include "game.hpp"
#include <iostream>
#include "../MovSystem/moving.hpp"
#include "../Ability/Attack_Around/around.hpp"
#include "../Ability/FarAttack/far.hpp"
#include "../Ability/Heal/heal.hpp"
#include "../Ability/Teleportation/teleportation.hpp"
#include "../Selector/selector.hpp"

enum EndState {
    Win,
    Lose
};

Game::Game(Map& m): map(m) {}

void Game::PlayerStep(Vriter& vriter) {
    std::cout << "Player (w/a/s/d, e = ability): ";
    std::string stp;
    std::getline(std::cin, stp);

    Player* player = map.findPlayer();
    if (!player) return;

    int steps = player->getSpeed();

    for (char step: stp) {
        if (step == 'w' || step == 's' || step == 'a' || step == 'd') {
            if (player->hasStatus(Slow_st)) {
                std::cout << "Slowing\n";
                break;
            }
            if (steps <= 0) break;
            int dx = 0, dy = 0;
            if (step == 'w') dx = -1;
            else if (step == 's') dx = 1;
            else if (step == 'a') dy = -1;
            else if (step == 'd') dy = 1;
            Mov::makeMove(map, dx, dy, *player, steps);
        }
        else if (step == 'e') {
            if (player->isOverloaded()) {
                player->removeStatus(Overload_st);
                std::cout << "Перегрузка\n";
                continue;
            }
            std::vector<std::unique_ptr<Ability>>& abs = player->getAbilities();

            if (abs.empty()) {
                std::cout << "No ability\n";
                continue;
            }

            for (size_t i = 0; i < abs.size(); i++)
                std::cout << i << ") " << abs[i]->getName() << "\n";

            std::cout << "Choose ability: ";
            std::string line;
            std::getline(std::cin, line);

            int index;
            try {
                index = std::stoi(line);
            }
            catch (...) {
                continue;
            }

            if (index < 0 || index >= abs.size()) {
                std::cout << "Choose error!\n";
                continue;
            }

            Ability* ability = abs[index].get();

            switch (ability->getType()) {
                case Around_ab: {
                    ability->use(*player, map, nullptr);
                    break;
                }
                case Heal_ab: {
                    ability->use(*player, map, nullptr);
                    break;
                }
                case Far_ab: {
                    int x_p = player->getPosition().first;
                    int y_p = player->getPosition().second;
                    std::vector<Enemy*> targets = Selector::EnemySelectorInRadius(map, x_p, y_p, 3);
                    if (targets.empty()) break;

                    vriter.setHighlight(targets);
                    vriter.printMap();
                    Enemy* target = Selector::selectEnemyInRange(targets);
                    vriter.clearHighlight();

                    ability->use(*player, map, target);
                    break;
                }
                case Teleport_ab: {
                    auto* tp = static_cast<Teleportation*>(ability);
                    if (player->getEnergy() < tp->getUsedEnergy()) {
                        std::cout << "Lacking energy\n";
                        break;
                    }
                    std::vector<std::pair<int, int>> cells = tp->collectValidCells(*player, map);
                    if (cells.empty()) break;

                    vriter.setGreenCells(cells);
                    vriter.printMap();

                    std::pair<int,int> user_pos = player->getPosition();
                    int px = user_pos.first;
                    int py = user_pos.second;

                    std::cout << "Bias (col row), exp: '0 -3': ";
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
                        std::cout << "Can't teleport there\n";
                        break;
                    }
                    tp->applyTeleport(*player, {targetRow, targetCol});
                    break;
                }
            }
        }
    }

    if (player->needsUpgradeChoice()) {
        handleRankUpChoice(*player);
        player->clearUpgradeFlag();
    }
}

void Game::handleRankUpChoice(Player& player) {
    std::cout << "\nRank upping! Rank " << player.getRank() << std::endl;

    const int MAX_ABILITIES = 4;
    bool hasAllAbilities = player.getAbilityCount() >= MAX_ABILITIES;

    if (!hasAllAbilities) {
        std::cout << "1) Gate new ability\n";
        std::cout << "2) Upgrade your\n";
        std::cout << "Choose: ";
        std::string line;
        std::getline(std::cin, line);

        if (line == "1") {
            chooseNewAbility(player);
            return;
        }
    }

    chooseUpgradeAbility(player);
}

void Game::chooseNewAbility(Player& player) {
    std::vector<AbilityType> available;
    if (!player.hasAbility(Around_ab))
        available.push_back(Around_ab);
    if (!player.hasAbility(Far_ab))
        available.push_back(Far_ab);
    if (!player.hasAbility(Heal_ab))
        available.push_back(Heal_ab);
    if (!player.hasAbility(Teleport_ab))
        available.push_back(Teleport_ab);

    std::cout << "Available abilities:\n";
    for (size_t i = 0; i < available.size(); ++i) {
        switch (available[i]) {
            case Around_ab: {
                std::cout << i << ") Around\n";
                break;
            }
            case Far_ab: {
                std::cout << i << ") Far\n";
                break;
            }
            case Heal_ab: {
                std::cout << i << ") Heal\n";
                break;
            }
            case Teleport_ab: {
                std::cout << i << ") Teleport\n";
                break;
            }
        }
    }
    std::cout << "Choose: ";
    std::string line;
    std::getline(std::cin, line);

    int idx;
    try {
        idx = std::stoi(line);
    }
    catch (...) {
        std::cout << "Not num\n"; return;
    }

    if (idx < 0 || idx >= available.size()) return;

    switch (available[idx]) {
        case Around_ab: {
            player.addAbility(std::make_unique<Around>(10, 1, 1));
            break;
        }
        case Far_ab: {
            player.addAbility(std::make_unique<Far>(8, 3, 1));
            break;
        }
        case Heal_ab: {
            player.addAbility(std::make_unique<Heal>(15, 1));
            break;
        }
        case Teleport_ab: {
            player.addAbility(std::make_unique<Teleportation>(5, 10));
            break;
        }
    }
    std::cout << "Ability acquired!\n";
}

void Game::chooseUpgradeAbility(Player& player) {
    auto& abs = player.getAbilities();
    if (abs.empty()) return;

    std::cout << "Choose ability for updating:\n";
    for (size_t i = 0; i < abs.size(); ++i)
        std::cout << i << ") " << abs[i]->getName() << "\n";

    std::cout << "Choose: ";
    std::string line;
    std::getline(std::cin, line);

    int idx;
    try {
        idx = std::stoi(line);
    }
    catch (...) {
        return;
    }

    if (idx < 0 || idx >= abs.size()) return;

    abs[idx]->upgrade();
}

void Game::enemyStep() {
    Player* player = map.findPlayer();
    if (!player) return;

    for (auto& enemy : map.getEnemies()) {
        if (!enemy.isAlive()) continue;
        if (enemy.getSpeed() == 0) continue;

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

    if (p->getHp() > 0) p->tickStatuses();
    for (auto& e : map.getEnemies())
        if (e.isAlive()) e.tickStatuses();
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