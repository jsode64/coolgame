// WIP, unused
#pragma once

#include <stdint.h>

#include "raylib.h"

#include "player.hpp"

class Attack {
    private:

        Rectangle hitbox;
        Rectangle hurtbox;
        Vector2 v1;
        Vector2 v2;
        Color color1;
        Color color2;

        bool attackHit;

        int32_t attackKey;

    public:

        Attack(Color color1, Color color2, int32_t attackKey);

        static constexpr float W = 10.0;

        static constexpr float H = 10.0;

        static constexpr float KB = 1000.0;

        /**
         * Updates the player.
         * 
         * @param player 
         */
        void update(const Player& p);

    private:

        // Checks collision with hurtbox.
        void collideWithHurtbox(const Rectangle& hurtbox);

        void moveWithPlayer(const Player& p);

        // Draws attack hitbox and hurtbox.
        void draw();

        void checkAttackKey(const Player& p);



};
