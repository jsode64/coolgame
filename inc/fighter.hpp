#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include "raylib.h"

#include "attack.hpp"
#include "stage.hpp"
#include "tile.hpp"

class Attack;

class Fighter {
    protected:

        Rectangle body;
        Vector2 v;

        float jumpSpeed;
        float acceleration;
        float decceleration;
        float maxSpeedH;

        std::optional<const Tile*> ground;

        int32_t leftKey;
        int32_t rightKey;
        int32_t jumpKey;
        int32_t attackKey;

    public:
    
        Fighter(Rectangle body, float jumpSpeed, float acceleration, float decceleration, float maxSpeedH, int32_t leftKey, int32_t rightKey, int32_t jumpKey, int32_t attackKey);

        /**
         * Respawns the fighter.
         */
        void respawn();

        /**
         * Returns the fighter's body.
         */
        Rectangle get_body() const;

        /**
         * Returns true if the fighter is on the ground, false if not.
         */
        bool on_ground() const;

        /**
         * Applies the knockback to the fighter.
         */
        void knock_back(Vector2 kb);

        /**
         * Updates the fighter.
         */
        virtual void update(const Stage& stage, std::vector<Attack>& attacks) = 0;

        /**
         * Draws the fighter.
         */
        virtual void draw() const = 0;

    // Ensure proper polymorphic destruction and vtable emission.
    virtual ~Fighter();

        /**
         * Returns a new ground attack.
         */
    virtual Attack ground_attack() = 0;

        /**
         * Returns a new air attack.
         */
    virtual Attack air_attack() = 0;

    protected:

        /**
         * Handles fighter movement via user input.
         * 
         * @param a Acceleration.
         * @param d Decceleration.
         * @param m Max horizontal speed.
         */
        void handle_movement();

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

        /**
         * Handles the fighter using an attack.
         */
        void handle_attacks(std::vector<Attack>& attacks);
};
