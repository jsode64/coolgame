#include "attack.hpp"

#include "raylib.h"

Attack::Attack(Fighter* src, Rectangle hitbox, Vector2 kb, std::function<bool(Attack&, std::vector<std::unique_ptr<Fighter>>&)> updateFn, std::function<void(const Attack&)> drawFn)
    : src(src), hitbox(hitbox), kb(kb), ticks(0), updateFn(updateFn), drawFn(drawFn) {

}

void Attack::set_hitbox(Rectangle hitbox_) {
    hitbox = hitbox_;
}

uint32_t Attack::get_ticks() const {
    return ticks;
}

bool Attack::update(std::vector<std::unique_ptr<Fighter>>& fighters) {
    bool done = updateFn(*this, fighters);
    ticks += 1;

    return done;
}

void Attack::handle_collision(std::vector<std::unique_ptr<Fighter>>& fighters) {
    for (auto& fighterPtr: fighters) {
        auto& fighter = *fighterPtr;
        // Skip source fighter.
        if (src == &fighter) {
            continue;
        }

        // Knock back if collided.
        if (CheckCollisionRecs(hitbox, fighter.get_body())) {
            fighter.knock_back(kb);
        }
    }
}

void Attack::draw() const {
    drawFn(*this);
}