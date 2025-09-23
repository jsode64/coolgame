#include "player.hpp"

#include "config.hpp"

// Build Player
Player::Player(Color color, int32_t leftKey, int32_t rightKey, int32_t upKey, int32_t downKey)
    : color(color), leftKey(leftKey), rightKey(rightKey), upKey(upKey), downKey(downKey) {
    respawn();
}

// Respawn function
void Player::respawn() {
    body = (Rectangle){
        (WIN_W - Player::W) / 2.0,
        (WIN_H - Player::H) / 2.0,
        Player::W,
        Player::H,
    };
    v = (Vector2){ 0, 0 };
    onGround = false;
}

// This updates the player condition.
void Player::update(const Stage& stage) {

    // Checks keystrokes
    if (IsKeyDown(KEY_R)) {
        respawn();
        return;
    }
    if (IsKeyDown(leftKey)) {
        v.x -= Player::ACCELERATION;
    }
    if (IsKeyDown(rightKey)) {
        v.x += Player::ACCELERATION;
    }
    if (IsKeyDown(upKey) && onGround) {
        v.y = -10;
        onGround = false;
    }
    if (onGround) {
        v.y = 0;
    }

    // Gravity
    v.y += Player::GRAVITY;

    // Velocity
    body.x += v.x;      
    body.y += v.y;

    // Collision
    auto [hit, rect] = stage.get_collision(body);

    if (hit) {
        body.y = rect.y - Player::H;
        onGround = true;
    } else {
        onGround = false;
    }

    // Deathzone
    if (body.x  > WIN_W || body.x + Player::W < 0 || body.y > WIN_H) {
        respawn();
    }
    
}

// Draws player (Obviously)
void Player::draw() const {
    DrawRectangleRec(body, color);
}
