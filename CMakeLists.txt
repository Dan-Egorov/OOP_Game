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
)
