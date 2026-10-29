#include <iostream>
#include <vector>

#include "Player/player.hpp"
#include "Enemy/enemy.hpp"
#include "GamePlace/place.hpp"
#include "Map/All_map.hpp"
#include "Game/game.hpp"
#include "Factory/factory.hpp"

#include "Status/status.hpp"
#include "Status/Slow/slow.hpp"
#include "Status/Overload/overload.hpp"
#include "Status/Burning/burning.hpp"
#include "Status/Shield/shield.hpp"
#include "Status/ItemPickup/item_pickup.hpp"

#include "Ability/Heal/heal.hpp"
#include "Ability/Teleportation/teleportation.hpp"
#include "Ability/FarAttack/far.hpp"
#include "Ability/Attack_Around/around.hpp"

#include "Config/GameConfig.hpp"

#include <random>

void generateMapStatuses(GamePlace& game) {
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> chance(1, 100);

    for (int i = 0; i < game.getSize().first; i++) {
        for (int j = 0; j < game.getSize().second; j++) {
            if (!game.getPlace()[i][j].pass) continue;

            int roll = chance(gen);

            if (roll <= 10) {
                int type = chance(gen) % 4;
                if (type == 0) game.getPlace()[i][j].pixelStates.push_back(std::make_shared<Slow>(1));
                else if (type == 1) game.getPlace()[i][j].pixelStates.push_back(std::make_shared<Burning>(Config::Statuses::BURNING_TURNS,
                    Config::Statuses::BURNING_DAMAGE));
                else if (type == 2) game.getPlace()[i][j].pixelStates.push_back(std::make_shared<Overload>());
                else game.getPlace()[i][j].pixelStates.push_back(std::make_shared<Shield>(Config::Statuses::SHIELD_DEFAULT_AMOUNT));
            }

            else if (roll <= 15) {
                game.getPlace()[i][j].pixelStates.push_back(std::make_shared<ItemPickup>());
            }
        }
    }
}

int main() {
    GamePlace game(10, 20);

    game.getPlace()[4][5].difficulty = 2;
    game.getPlace()[4][6].difficulty = 2;
    game.getPlace()[4][7].difficulty = 2;
    game.getPlace()[7][10].difficulty = 3;
    game.getPlace()[7][11].difficulty = 3;

    for (int i = 2; i < 18; i++) game.getPlace()[2][i].pass = false;
    for (int i = 3; i < 8;  i++) game.getPlace()[i][3].pass = false;

    Player player(Config::Player::START_HP,
        Config::Player::START_HP_MAX,
        Config::Player::START_POWER,
        Config::Player::START_ENERGY,
        Config::Player::START_MAX_ENERGY,
        Config::Player::START_SPEED,
        Config::Player::START_VISION);
    player.setPosition({0, 1});

    std::vector<Enemy> enemies;
    Enemy e1(Config::Enemy::DEFAULT_HP,
        Config::Enemy::DEFAULT_HP_MAX,
        Config::Enemy::DEFAULT_POWER,
        Config::Enemy::DEFAULT_ENERGY,
        Config::Enemy::DEFAULT_MAX_ENERGY,
        Config::Enemy::DEFAULT_SPEED,
        Config::Enemy::DEFAULT_VISION);
    e1.setPosition({1, 1});
    enemies.push_back(e1);

    Enemy e2(Config::Enemy::DEFAULT_HP,
        Config::Enemy::DEFAULT_HP_MAX,
        Config::Enemy::DEFAULT_POWER,
        Config::Enemy::DEFAULT_ENERGY,
        Config::Enemy::DEFAULT_MAX_ENERGY,
        Config::Enemy::DEFAULT_SPEED,
        Config::Enemy::DEFAULT_VISION);
    e2.setPosition({3, 1});
    enemies.push_back(e2);

    Map map(game, &player, enemies);
    map.addFactory(Factory({8, 17}, 5));

    std::cout << "Choose starting ability:\n0) Around\n1) Far\n2) Heal\n3) Teleport\n> ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();
    if (choice == 0) player.addAbility(std::make_shared<Around>(10, 1, 2));
    else if (choice == 1) player.addAbility(std::make_shared<Far>(8, 3, 2));
    else if (choice == 2) player.addAbility(std::make_shared<Heal>(15, 2));
    else player.addAbility(std::make_shared<Teleportation>(5, 10));

    generateMapStatuses(game);

    Game play(map);
    play.run();
    return 0;
}