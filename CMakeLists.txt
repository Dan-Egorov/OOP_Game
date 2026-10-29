cmake_minimum_required(VERSION 4.3)
project(OOP_game)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/Robot,
        src/Game,
        src/GamePlace,
        src/Map,
        src/MovSystem,
        src/Factory,
        src/Map
)

add_executable(OOP_game
        src/Robot/robot.cpp
        src/main.cpp
        src/GamePlace/place.cpp
        src/MovSystem/moving.cpp
        src/Map/All_map.cpp
        src/Visual/drawer.cpp
        src/Game/game.cpp
        src/Factory/factory.cpp
        src/Enemy/enemy.cpp
        src/Player/player.cpp

        src/Selector/selector.cpp

        src/Ability/interface.cpp
        src/Ability/Teleportation/teleportation.cpp
        src/Ability/Attack_Around/around.cpp
        src/Ability/Heal/heal.cpp
        src/Ability/FarAttack/far.cpp

        src/Status/status.cpp
        src/Status/Slow/slow.cpp
        src/Status/Overload/overload.cpp
        src/Status/Burning/burning.cpp
        src/Status/Shield/shield.cpp

        src/Item/HealthPotion/health_potion.cpp
        src/Item/EnergyPotion/energy_potion.cpp
        src/Item/AttackBoost/attack_boost.cpp
        src/Status/AttackBuff/attack_buff.cpp
        src/Status/ItemPickup/item_pickup.cpp
)
