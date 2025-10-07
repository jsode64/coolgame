// WIP, unused
#pragma once

#include <stdint.h>
#include <functional>

#include "raylib.h"

#include "fighter.hpp"
#include <memory>
#include <vector>

class Fighter;

class Attack {
    private:
        // The fighter the attack came from.
        Fighter* src;

        // Attack collision box.
        Rectangle hitbox;

        // Attack knockback.
        Vector2 kb;

        // The number of ticks the attack has been alive for.
        uint32_t ticks;

        // Attack update
        std::function<bool(Attack&, std::vector<std::unique_ptr<Fighter>>&)> updateFn;

        // Draw callback.
        std::function<void(const Attack&)> drawFn;

    public:

        Attack(Fighter* src, Rectangle hitbox, Vector2 kb, std::function<bool(Attack&, std::vector<std::unique_ptr<Fighter>>&)> updateFn, std::function<void(const Attack&)> drawFn);

        // Sets the attack's hitbox.
        void set_hitbox(Rectangle hitbox);

        // Returns the attack's tick lifetime.
        uint32_t get_ticks() const;

        // Updates the attack. Returns true if the attack is finished and should be removed.
        bool update(std::vector<std::unique_ptr<Fighter>>& fighters);

        // Draws the attack.
        void draw() const;

        // Checks for collision with the given fighters and knocks them back.
        void handle_collision(std::vector<std::unique_ptr<Fighter>>& fighters);
};
