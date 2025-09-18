#include "player.hpp"

#include "config.hpp"

Player::Player(Color color, int32_t leftKey, int32_t rightKey, int32_t upKey, int32_t downKey)
    : color(color), leftKey(leftKey), rightKey(rightKey), upKey(upKey), downKey(downKey) {
    respawn();
}

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

void Player::update(const Stage& stage) {
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

    v.y += Player::GRAITY;

    body.x += v.x;
    body.y += v.y;

    if (CheckCollisionRecs(body, stage.get_body())) {
        body.y = stage.get_body().y - Player::H;
        onGround = true;
    }
}

void Player::draw() const {
    DrawRectangleRec(body, color);
}
