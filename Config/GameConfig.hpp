#pragma once

namespace Config {
    namespace Map {
        constexpr int MIN_SIZE = 5;
        constexpr int MAX_SIZE = 20;
    }

    namespace Player {
        constexpr int START_HP = 10;
        constexpr int START_HP_MAX = 10;
        constexpr int START_POWER = 5;
        constexpr int START_ENERGY = 5;
        constexpr int START_MAX_ENERGY = 5;
        constexpr int START_SPEED = 2;
        constexpr int START_VISION = 5;
        constexpr int EXP_TO_RANK_UP = 5;
    }

    namespace Enemy {
        constexpr int DEFAULT_HP = 15;
        constexpr int DEFAULT_HP_MAX = 15;
        constexpr int DEFAULT_POWER = 5;
        constexpr int DEFAULT_ENERGY = 5;
        constexpr int DEFAULT_MAX_ENERGY = 10;
        constexpr int DEFAULT_SPEED = 3;
        constexpr int DEFAULT_VISION = 3;
    }

    namespace Abilities {
        // Around
        constexpr int AROUND_DAMAGE = 10;
        constexpr int AROUND_RADIUS = 1;
        constexpr int AROUND_ENERGY = 2;

        // Far
        constexpr int FAR_DAMAGE = 8;
        constexpr int FAR_RADIUS = 3;
        constexpr int FAR_ENERGY = 2;

        // Heal
        constexpr int HEAL_AMOUNT = 15;
        constexpr int HEAL_ENERGY = 2;

        // Teleport
        constexpr int TELEPORT_RANGE = 5;
        constexpr int TELEPORT_ENERGY = 10;
    }

    namespace Items {
        constexpr int HEALTH_POTION_HEAL = 20;
        constexpr int ENERGY_POTION_RESTORE = 15;
        constexpr int ATTACK_BOOST_AMOUNT = 5;
        constexpr int ATTACK_BOOST_TURNS = 3;
    }

    namespace Statuses {
        constexpr int BURNING_DAMAGE = 2;
        constexpr int BURNING_TURNS = 3;
        constexpr int SHIELD_DEFAULT_AMOUNT = 10;
    }

    namespace Gameplay {
        constexpr int TURN_ENERGY_REGEN = 5;
        constexpr int TURN_HP_REGEN = 1;
    }
}