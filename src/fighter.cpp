#include "fighter.hpp"
#include "attack.hpp"
#include "game.hpp"
#include "stage.hpp"
#include "tile.hpp"

#include <algorithm>

#include "config.hpp"

Fighter::Fighter(Rectangle body, float jumpSpeed, float acceleration,
                 float decceleration, float maxSpeedH, int32_t leftKey,
                 int32_t rightKey, int32_t jumpKey, int32_t attackKey)
    : body(body), v(0.0f, 0.0f), jumpSpeed(jumpSpeed),
      acceleration(acceleration), decceleration(decceleration),
      maxSpeedH(maxSpeedH), ground(std::nullopt), leftKey(leftKey),
      rightKey(rightKey), jumpKey(jumpKey), attackKey(attackKey) {}

void Fighter::respawn() {
  body.x = (float(WIN_W) - body.width) / 2.0;
  body.y = (float(WIN_H) - body.height) / 2.0;

  v = Vector2(0.0f, 0.0f);

  ground = std::nullopt;
}

Rectangle Fighter::get_body() const { return body; }

bool Fighter::on_ground() const { return ground.has_value(); }

void Fighter::knock_back(Vector2 kb) {
  v.x += kb.x;
  v.y += kb.y;
}

void Fighter::update(Game &game) {
  handle_movement();
  handle_oob();
  handle_collision(game.get_stage());
  handle_attacks(game.get_attacks());
}

void Fighter::handle_movement() {
  // Horizontal movement.
  bool left = IsKeyDown(leftKey);
  bool right = IsKeyDown(rightKey);
  bool hMove = left != right;
  if (left) {
    v.x -= std::clamp(v.x - -maxSpeedH, 0.0f, acceleration);
    hMove = true;
  }
  if (right) {
    v.x += std::clamp(maxSpeedH - v.x, 0.0f, acceleration);
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
    v.x = (std::abs(v.x) <= decceleration)
              ? 0.0f
              : v.x - std::copysign(decceleration, v.x);
  }

  // Limit player speed.
  v.y = std::min(v.y, 2.0f * maxSpeedH);
}

void Fighter::handle_oob() {
  bool oob = body.x <= -body.width || body.x >= WIN_W || body.y >= WIN_H;

  if (oob) {
    respawn();
  }
}

void Fighter::handle_collision(Stage &stage) {
  float x = body.x + v.x;
  float y = body.y + v.y;

  // If on a tile, move with it.
  if (ground.has_value()) {
    auto floor = ground.value();
    x += floor->v.x;
  }

  ground = std::nullopt;

  for (auto &tile : stage.get_bodies()) {
    // Horizontal collision check.
    auto testBody = Rectangle(x, body.y, body.width, body.height);
    auto pre = tile;
    pre.body.y -= tile.v.y;
    if (CheckCollisionRecs(testBody, tile.body) &&
        CheckCollisionRecs(testBody, pre.body)) {
      if (v.x > 0.0f) {
        // Both moving right, tile faster:
        if (tile.v.x > v.x) {
          x = tile.body.x + tile.body.width;
          v.x += tile.v.x;
        } else {
          x = tile.body.x - body.width;
          v.x = 0.0f;
        }
      } else if (v.x < 0.0f) {
        // Both moving left, tile faster:
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
    testBody = Rectangle(x, y, body.width, body.height);
    if (CheckCollisionRecs(testBody, tile.body)) {
      if (v.y >= 0.0f) {
        y = tile.body.y - body.height;

        // On ground.
        ground = std::optional<const Tile *>{&tile};
        tile.stood_on();
      } else {
        y = tile.body.y + tile.body.height;
      }
      v.y = 0;
    }
  }

  // Move to new position.
  body.x = x;
  body.y = y;
}

void Fighter::handle_attacks(std::vector<std::unique_ptr<Attack>> &attacks) {
  if (IsKeyDown(attackKey)) {
    if (on_ground()) {
      attacks.push_back(ground_attack());
    } else {
      attacks.push_back(air_attack());
    }
  }
}
