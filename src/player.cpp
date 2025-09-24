#include "player.hpp"

#include <algorithm>
#include <cmath>

#include "config.hpp"
#include "util.hpp"

Player::Player(Color color, int32_t leftKey, int32_t rightKey, int32_t upKey, int32_t downKey)
    : color(color), leftKey(leftKey), rightKey(rightKey), upKey(upKey), downKey(downKey) {
    respawn();
}

void Player::respawn() {
    // Place in center of screen.
    body = (Rectangle){
        (WIN_W - Player::W) / 2.0f,
        (WIN_H - Player::H) / 2.0f,
        Player::W,
        Player::H,
    };

    // Make immobile and airborn.
    v = (Vector2){ 0.0f, 0.0f };
    onGround = false;
}

void Player::update(const Stage& stage) {
    do_movement();
    handle_oob();
    collide_with(stage);
}

void Player::draw() const {
    DrawRectangleRec(body, color);
}

void Player::do_movement() {
    // Horizontal movement.
    bool hMove = false;
    if (IsKeyDown(leftKey)) {
        v.x -= ACCELERATION;
        hMove = true;
    }
    if (IsKeyDown(rightKey)) {
        v.x += ACCELERATION;
        hMove = true;
    }

    // Vertical movement.
    if (IsKeyDown(upKey) && onGround) {
        v.y = -JUMP_SPEED;
    } else {
        v.y += GRAVITY;
    }

    // Deccelerate if no horizontal movement key was pressed.
    if (!hMove) {
        v.x -= (std::abs(v.x) <= DECCELERATION) ? v.x : std::copysign(DECCELERATION, v.x);
    }

    // Limit player speed.
    v.x = std::clamp(v.x, -MAX_SPEED, MAX_SPEED);
    v.y = std::min(v.y, 2.0f * MAX_SPEED);
}

void Player::handle_oob() {
    bool oob = body.x < -body.width
        || body.x > WIN_W
        || body.y > WIN_H;
    
    if (oob) {
        respawn();
    }
}

void Player::collide_with(const Stage& stage) {
    float x = body.x + v.x;
    float y = body.y + v.y;
    onGround = false;

    for (const auto& rect : stage.get_bodies()) {
        // Horizontal collision check.
        auto testBody = (Rectangle){ x, body.y, body.width, body.height };
        if (recs_collide(testBody, rect)) {
            if (v.x > 0.0f) {
                x = rect.x - body.width;
            } else {
                x = rect.x + rect.width;
            }
            v.x = 0.0f;
        }

        // Vertical collision check.
        testBody = (Rectangle){ x, y, body.width, body.height };
        if (recs_collide(testBody, rect)) {
            if (v.y >= 0.0f) {
                y = rect.y - body.height;
                onGround = true;
            } else {
                y = rect.y + rect.height;
            }
            v.y = 0.0f;
        }
    }

    // Move to new position.
    body.x = x;
    body.y = y;
}
