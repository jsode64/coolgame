#pragma once

#include <stdint.h>

#include "raylib.h"

#include "stage.hpp"

class Player {
    private: 

        Rectangle body;
        Vector2 v;
        Color color;

        bool onGround;

        int32_t leftKey;
        int32_t rightKey;
        int32_t upKey;
        int32_t downKey;
    
    public:

        static constexpr float ACCELERATION = 0.5;
        static constexpr float DECCELERATION = ACCELERATION / 2.0;
        static constexpr float MAX_SPEED = 5.0;
        static constexpr float JUMP_SPEED = 10.0;
        static constexpr float GRAVITY = 0.5;

        static constexpr float W = 15.0;
        static constexpr float H = 20.0;

        Player(Color color, int32_t leftKey, int32_t rightKey, int32_t upKey, int32_t downKey);

        /**
         * Respawns the player.
         */
        void respawn();

        /**
         * Updates the player.
         * 
         * @param stage The stage to collide with.
         */
        void update(const Stage& stage);

        /**
         * Draws the player to the screen.
         */
        void draw() const;

    private:
        // Player update methods, in the order they are called in `Player::update`:

        /**
         * Handles player movement from user input.
         */
        void do_movement();

        /**
         * Checks if the player is OOB and respawns it if it is.
         */
        void handle_oob();

        /**
         * Handles player collision with the given stage.
         */
        void collide_with(const Stage& stage);
};
