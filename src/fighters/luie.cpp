#include "fighters/luie.hpp"

Luie::Luie(int32_t leftKey, int32_t rightKey, int32_t jumpKey)
    : Fighter(Rectangle({ 0.0f, 0.0f, 10.0f, 30.0f }), 15.0f, leftKey, rightKey, jumpKey) {
    respawn();
}

void Luie::update(const Stage& stage) {
    handle_movement(ACCELERATION, DECCELERATION, MAX_SPEED);
    handle_oob();
    handle_collision(stage);
}

void Luie::draw() const {
    DrawRectangleRec(body, GREEN);
}
