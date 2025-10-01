#include "player.hpp"

#include <algorithm>
#include <cmath>

#include "config.hpp"

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
    ground = std::nullopt;
}

void Player::update(const Stage& stage) {
    do_movement();
    handle_oob();
    handle_collision(stage);
}

void Player::draw() const {
    DrawRectangleRec(body, color);
}

Rectangle Player::get_body() const {
    return body;
}

void Player::do_movement() {
    // Horizontal movement.
    bool left = IsKeyDown(leftKey);
    bool right = IsKeyDown(rightKey);
    bool hMove = left != right;
    if (left) {
        v.x -= std::clamp(v.x - -MAX_SPEED, 0.0f, ACCELERATION);
        hMove = true;
    }
    if (right) {
        v.x += std::clamp(MAX_SPEED - v.x, 0.0f, ACCELERATION);
        hMove = true;
    }

    // Vertical movement.
    if (IsKeyDown(upKey) && ground.has_value()) {
        v.y = -JUMP_SPEED;
        v.x += ground.value()->v.x;
    } else {
        v.y += GRAVITY;
    }

    // Deccelerate if neutral input or moving against current direction.
    if (!hMove || (left && v.x > 0.0f) || (right && v.x < 0.0f)) {
        v.x = (std::abs(v.x) <= DECCELERATION) ? 0.0f : v.x - std::copysign(DECCELERATION, v.x);
    }

    // Limit player speed.
    //v.x = std::clamp(v.x, -MAX_SPEED, MAX_SPEED);
    v.y = std::min(v.y, 2.0f * MAX_SPEED);
}

void Player::handle_oob() {
    bool oob = body.x <= -body.width
        || body.x >= WIN_W
        || body.y >= WIN_H;
    
    if (oob) {
        respawn();
    }
}

void Player::handle_collision(const Stage& stage) {
    float x = body.x + v.x;
    float y = body.y + v.y;

    // If on a tile, move with it.
    if (ground.has_value()) {
        x += ground.value()->v.x;
    }

    ground = std::nullopt;

    for (const auto& tile : stage.get_bodies()) {
        // Horizontal collision check.
        auto testBody = (Rectangle){ x, body.y, body.width, body.height };
        if (CheckCollisionRecs(testBody, tile.body)) {
            if (v.x > 0.0f) {
                if (tile.v.x > v.x) {
                    x = tile.body.x + tile.body.width;
                    v.x += tile.v.x;
                } else {
                    x = tile.body.x - body.width;
                    v.x = 0.0f;
                }
            } else if (v.x < 0.0f) {
                if (tile.v.x < v.x) {
                    x = tile.body.x - body.width;
                    v.x += tile.v.x;
                } else {
                    x = tile.body.x + tile.body.width;
                    v.x = 0.0f;
                }
            } else {
                // Player not moving, tile must have hit them.
                if (tile.v.x > 0.0f) {
                    x = tile.body.x + tile.body.width;
                } else {
                    x = tile.body.x - body.width;
                }
                v.x += tile.v.x;
            }
        }

        // Vertical collision check.
        testBody = (Rectangle){ x, y, body.width, body.height };
        if (CheckCollisionRecs(testBody, tile.body)) {
            if (v.y >= 0.0f) {
                y = tile.body.y - body.height;

                // On ground.
                ground = std::optional<const Tile*>{ &tile };
                y += tile.v.y;
            } else {
                y = tile.body.y + tile.body.height;
            }
            v.y = 0.0f;
        }
    }

    // Move to new position.
    body.x = x;
    body.y = y;
}
