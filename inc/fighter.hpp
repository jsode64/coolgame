#pragma once

#include <cstdint>
#include <optional>

#include "raylib.h"

#include "stage.hpp"
#include "tile.hpp"

class Fighter {
    protected:

        Rectangle body;
        Vector2 v;

        float jumpSpeed;
        std::optional<const Tile*> ground;

        int32_t leftKey;
        int32_t rightKey;
        int32_t jumpKey;

    public:
    
        Fighter(Rectangle body, float jumpSpeed, int32_t leftKey, int32_t rightKey, int32_t jumpKey);

        /**
         * Respawns the player.
         */
        void respawn();

        /**
         * Returns the player's body.
         */
        Rectangle get_body() const;

        /**
         * Updates the player.
         */
        virtual void update(const Stage& stage) = 0;

        /**
         * Draws the player.
         */
        virtual void draw() const = 0;

    protected:

        /**
         * Handles fighter movement via user input.
         * 
         * @param a Acceleration.
         * @param d Decceleration.
         * @param m Max horizontal speed.
         */
        void handle_movement(float a, float d, float m);

        /**
         * Handles player being OOB (out of bounds).
         */
        void handle_oob();

        /**
         * Handles player collision.
         * 
         * @param stage The stage to collide with.
         */
        void handle_collision(const Stage& stage);
};
