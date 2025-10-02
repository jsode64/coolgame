#include "fighter.hpp"

#include <algorithm>

#include "config.hpp"

Fighter::Fighter(Rectangle body, float jumpSpeed, int32_t leftKey, int32_t rightKey, int32_t jumpKey)
    : body(body), v({ 0.0f, 0.0f }), jumpSpeed(jumpSpeed), ground(std::nullopt), leftKey(leftKey), rightKey(rightKey), jumpKey(jumpKey) {

}

void Fighter::respawn() {
    body.x = (float(WIN_W) - body.width) / 2.0;
    body.y = (float(WIN_H) - body.height) / 2.0;

    v = { 0.0f, 0.0f };

    ground = std::nullopt;
}

void Fighter::handle_movement(float a, float d, float m) {
    // Horizontal movement.
    bool left = IsKeyDown(leftKey);
    bool right = IsKeyDown(rightKey);
    bool hMove = left != right;
    if (left) {
        v.x -= std::clamp(v.x - -m, 0.0f, a);
        hMove = true;
    }
    if (right) {
        v.x += std::clamp(m - v.x, 0.0f, a);
        hMove = true;
    }

    // Vertical movement.
    if (IsKeyDown(jumpKey) && ground.has_value()) {
        v.y = -jumpSpeed;
        v.x += ground.value()->v.x;
    } else {
        v.y += GRAVITY;
    }

    // Deccelerate if neutral input or moving against current direction.
    if (!hMove || (left && v.x > 0.0f) || (right && v.x < 0.0f)) {
        v.x = (std::abs(v.x) <= d) ? 0.0f : v.x - std::copysign(d, v.x);
    }

    // Limit player speed.
    v.y = std::min(v.y, 2.0f * m);
}

void Fighter::handle_oob() {
    bool oob = body.x <= -body.width
        || body.x >= WIN_W
        || body.y >= WIN_H;
    
    if (oob) {
        respawn();
    }
}

void Fighter::handle_collision(const Stage& stage) {
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
