#pragma once
#include <string>
#include <vector>
#include "../Robot/robot.hpp"
//#include "../Map/All_map.hpp"
//#include "../Player/player.hpp"


class Map;
class Player;
class Enemy;

enum AbilityType {
    Around_ab,
    Far_ab,
    Heal_ab,
    Teleport_ab
};

class  Ability {
public:
    virtual ~Ability() = default;
    virtual int getUsedEnergy() = 0;
    virtual std::string getName() = 0;
    virtual void use(Player& robot, Map& map, Enemy* target) = 0;
};