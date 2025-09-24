// WIP, unused
#pragma once

#include <stdint.h>

#include "raylib.h"

class Attack {
    private:
        Rectangle hitbox;
        Rectangle hurtbox;
        Color color;

        bool attackHit;

        int32_t attackKey;

    public:

        Attack(Color color, int32_t attackKey);

        /// @brief Draws attack hitbox
        void draw() whenAttack;

        /// @param player
        void update (const Player& player);

        static constexpr float W = 100.0;

        static constexpr float H = 10.0;




};
