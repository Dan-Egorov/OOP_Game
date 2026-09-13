#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

#include "Robot/robot.hpp"
#include "GamePlace/place.hpp"
#include "Map/All_map.hpp"
#include "MovSystem/moving.hpp"
#include "Visual/drawer.hpp"
#include "Game/game.hpp"
#include "Factory/factory.hpp"

/* Compiling

g++ -std=c++17 -I. \
    test.cpp \
    Robot/robot.cpp \
    GamePlace/place.cpp \
    Map/All_map.cpp \
    MovSystem/moving.cpp \
    Visual/drawer.cpp \
    Game/game.cpp \
    Factory/factory.cpp \
    -o test_all

*/

// Robot
void test_robot() {
    Robot r(10, 20, 5, 8, 10, PLAYER);
    assert(r.getHp() == 10);
    assert(r.getHpMax() == 20);
    assert(r.getPower() == 5);
    assert(r.getEnergy() == 8);
    assert(r.getMaxEnergy() == 10);
    assert(r.getExp() == 0);
    assert(r.getExpNewRang() == 10);
    assert(r.getType() == PLAYER);
    assert(r.getSpeed() == 3);
    assert(r.getVision() == 1);

    r.setHp(15);
    assert(r.getHp() == 15);
    r.setPosition({3, 4});
    assert(r.getPosition().first == 3);
    assert(r.getPosition().second == 4);
    r.setSpeed(0);
    assert(r.getSpeed() == 1);
    r.setVision(0);
    assert(r.getVision() == 1);

    // botAttack
    Robot attacker(10, 20, 5, 8, 10, PLAYER);
    Robot target(15, 20, 3, 5, 10, ENEMY);
    attacker.botAttack(target);
    assert(target.getHp() == 10);
    assert(attacker.getExp() == 1);

    // botHeal
    Robot healer(10, 20, 5, 8, 10, PLAYER);
    Robot wounded(15, 20, 3, 5, 10, PLAYER);
    healer.botHeal(wounded);
    assert(wounded.getHp() == 20);

    // botAction
    Robot player(10, 20, 5, 8, 10, PLAYER);
    Robot enemy(10, 20, 5, 8, 10, ENEMY);
    Robot ally(10, 20, 5, 8, 10, PLAYER);
    player.botAction(enemy);
    assert(enemy.getHp() == 5);
    ally.setHp(5);
    player.botAction(ally);
    assert(ally.getHp() == 10);
}

// GamePlace
void test_gameplace() {
    GamePlace gp(10, 20);
    assert(gp.getSize().first == 10);
    assert(gp.getSize().second == 20);
    assert(gp.getPlace().size() == 10);
    assert(gp.getPlace()[0].size() == 20);
    assert(gp.isPassable(0, 0) == true);
    assert(gp.getDifficulty(0, 0) == 1);

    gp.getPlace()[2][3].pass = false;
    gp.getPlace()[2][3].difficulty = 3;
    assert(gp.isPassable(2, 3) == false);
    assert(gp.getDifficulty(2, 3) == 3);

    bool thrown = false;
    try {
        GamePlace bad(4, 5);
    }
    catch (const std::invalid_argument&) {
        thrown = true;
    }
    assert(thrown);
}

// Map
void test_map() {
    GamePlace place(10, 10);
    std::vector<Robot> robots;
    Robot p(10, 20, 5, 8, 10, PLAYER);
    p.setPosition({0, 0});
    robots.push_back(p);
    Robot e(10, 20, 5, 8, 10, ENEMY);
    e.setPosition({1, 1});
    robots.push_back(e);

    Map map(place, robots);
    assert(map.getSize().first == 10);
    assert(map.getRobots().size() == 2);
    assert(map.getFactories().size() == 0);

    map.addFactory(Factory({5, 5}, 3));
    assert(map.getFactories().size() == 1);
    assert(map.factoryHere(5, 5) == true);
    assert(map.factoryHere(6, 6) == true);
    assert(map.factoryHere(7, 7) == false);

    assert(map.botHere(0, 0) == true);
    assert(map.botHere(9, 9) == false);
    assert(map.walHere(0, 0) == false);
    place.getPlace()[3][3].pass = false;
    assert(map.walHere(3, 3) == true);

    assert(map.robotAt(0, 0) != nullptr);
    assert(map.robotAt(0, 0)->getType() == PLAYER);
    assert(map.robotAt(9, 9) == nullptr);

    Robot* found = map.findPlayer();
    assert(found != nullptr);
    assert(found->getType() == PLAYER);
}

// Mov
void test_mov() {
    GamePlace place(10, 10);
    std::vector<Robot> robots;
    Robot p(10, 20, 5, 8, 10, PLAYER);
    p.setPosition({0, 0});
    p.setSpeed(3);
    robots.push_back(p);

    Map map(place, robots);
    assert(Mov::makeMove(map, 0, 0, map.getRobots()[0]) == false);
    assert(Mov::makeMove(map, 1, 0, map.getRobots()[0]) == true);
    assert(map.getRobots()[0].getPosition().first == 3);

    GamePlace place2(10, 10);
    std::vector<Robot> robots2;
    Robot p2(10, 20, 5, 8, 10, PLAYER);
    p2.setPosition({0, 0});
    p2.setSpeed(3);
    robots2.push_back(p2);

    Map map2(place2, robots2);
    place2.getPlace()[0][1].difficulty = 2;
    assert(Mov::makeMove(map2, 0, 1, map2.getRobots()[0]) == true);
    assert(map2.getRobots()[0].getPosition().second == 2);

    GamePlace place3(10, 10);
    std::vector<Robot> robots3;
    Robot p3(10, 20, 5, 8, 10, PLAYER);
    p3.setPosition({0, 0});
    p3.setSpeed(3);
    robots3.push_back(p3);

    Map map3(place3, robots3);
    place3.getPlace()[0][1].pass = false;
    assert(Mov::makeMove(map3, 0, 1, map3.getRobots()[0]) == false);
    assert(map3.getRobots()[0].getPosition().second == 0);
    assert(Mov::makeMove(map3, -1, 0, map3.getRobots()[0]) == false);
}

// Vriter
void test_vriter() {
    GamePlace place(5, 5);
    std::vector<Robot> robots;
    Robot p(10, 20, 5, 8, 10, PLAYER);
    p.setPosition({0, 0});
    p.setVision(3);
    robots.push_back(p);

    Map map(place, robots);
    place.getPlace()[1][1].pass = false;
    Vriter vriter(map);

    std::stringstream buf;
    std::streambuf* old = std::cout.rdbuf(buf.rdbuf());
    vriter.printMap();
    std::cout.rdbuf(old);

    std::string out = buf.str();
    assert(out.find('p') != std::string::npos);
    assert(out.find('o') != std::string::npos);
    assert(out.find('?') != std::string::npos);
    assert(map.getVisibleWals().size() == 1);
    assert(map.getVisibleWals()[0].first == 1);
    assert(map.getVisibleWals()[0].second == 1);
}

// Game
void test_game() {
    GamePlace place(10, 10);
    std::vector<Robot> robots;
    Robot p(10, 20, 5, 8, 10, PLAYER);
    p.setPosition({0, 0});
    p.setSpeed(3);
    p.setEnergy(3);
    p.setHp(5);
    robots.push_back(p);
    Robot e(10, 20, 5, 8, 10, ENEMY);
    e.setPosition({5, 5});
    e.setSpeed(1);
    e.setEnergy(7);
    e.setHp(8);
    robots.push_back(e);

    Map map(place, robots);
    Game game(map);
    assert(game.allEnemiesDead() == false);
    assert(game.playerDead() == false);

    game.endSteps();
    assert(map.getRobots()[0].getEnergy() == 8);
    assert(map.getRobots()[0].getHp() == 6);
    assert(map.getRobots()[1].getEnergy() == 12);
    assert(map.getRobots()[1].getHp() == 9);

    int oldRow = map.getRobots()[1].getPosition().first;
    game.enemyStep();
    assert(map.getRobots()[1].getPosition().first == oldRow - 1);

    map.addFactory(Factory({8, 8}, 1));
    int before = map.getRobots().size();
    game.factoryStep();
    assert(map.getRobots().size() == before + 1);

    map.getRobots()[0].setHp(0);
    assert(game.playerDead() == true);

    for (auto& r : map.getRobots()) {
        if (r.getType() == ENEMY) r.setHp(0);
    }
    assert(game.allEnemiesDead() == true);
}

// Factory
void test_factory() {
    Factory f({2, 3}, 5);
    assert(f.getPosition().first == 2);
    assert(f.getPosition().second == 3);
    assert(f.getPeriod() == 5);
    assert(f.getCounter() == 0);

    Factory f2({0, 0}, 0);
    assert(f2.getPeriod() == 1);
    Factory f3({0, 0}, -5);
    assert(f3.getPeriod() == 1);

    assert(f.occupies(2, 3) == true);
    assert(f.occupies(2, 4) == true);
    assert(f.occupies(3, 3) == true);
    assert(f.occupies(3, 4) == true);
    assert(f.occupies(2, 2) == false);
    assert(f.occupies(4, 4) == false);

    GamePlace place(10, 10);
    std::vector<Robot> robots;
    Map map(place, robots);
    Factory factory({5, 5}, 3);
    assert(factory.tick(map) == false);
    assert(factory.tick(map) == false);
    assert(factory.tick(map) == true);
    assert(factory.getCounter() == 0);
    assert(robots.size() == 1);
    assert(robots[0].getType() == ENEMY);
}

int main() {
    test_robot();
    std::cout << "Robot     OK" << std::endl;
    test_gameplace();
    std::cout << "GamePlace OK" << std::endl;
    test_map();
    std::cout << "Map       OK" << std::endl;
    test_mov();
    std::cout << "Mov       OK" << std::endl;
    test_vriter();
    std::cout << "Vriter    OK" << std::endl;
    test_game();
    std::cout << "Game      OK" << std::endl;
    test_factory();
    std::cout << "Factory   OK" << std::endl;

    std::cout << std::endl;
    std::cout << "Все тесты пройдены." << std::endl;
    return 0;
}