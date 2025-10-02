#include "fighters/oscar.hpp"

Oscar::Oscar(int32_t leftKey, int32_t rightKey, int32_t jumpKey)
    : Fighter(Rectangle({ 0.0f, 0.0f, 50.0f, 50.0f }), 10.0f, leftKey, rightKey, jumpKey) {
    respawn();
}

void Oscar::update(const Stage& stage) {
    handle_movement(ACCELERATION, DECCELERATION, MAX_SPEED);
    handle_oob();
    handle_collision(stage);
}

void Oscar::draw() const {
    DrawRectangleRec(body, RED);
}
