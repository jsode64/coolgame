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

        static constexpr float GRAITY = 0.5;

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
};
