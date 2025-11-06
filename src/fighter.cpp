#include "fighter.hpp"
#include "attack.hpp"
#include "game.hpp"
#include "stage.hpp"
#include "tile.hpp"

#include <algorithm>
#include <iostream>

#include "config.hpp"

Fighter::Fighter(Rectangle body, float jumpSpeed, float acceleration,
                 float decceleration, float maxSpeedH, int32_t leftKey,
                 int32_t rightKey, int32_t jumpKey, int32_t attackKey)
    : body(body), jumpSpeed(jumpSpeed), acceleration(acceleration),
      decceleration(decceleration), maxSpeedH(maxSpeedH), leftKey(leftKey),
      rightKey(rightKey), jumpKey(jumpKey), attackKey(attackKey) {
  v = Vector2(0.0f, 0.0f);
  dir = Dir::RIGHT;

  action = Action::IDLE;
  aFrames = 0;

  percentage = 0.f;
  iFrames = 0;
  cooldown = 0;

  ground = std::nullopt;
}

void Fighter::respawn() {
  body.x = (float(WIN_W) - body.width) / 2.f;
  body.y = (float(WIN_H) - body.height) / 2.f;

  v = Vector2(0.0f, 0.0f);

  ground = std::nullopt;

  percentage = 0.f;
}

Dir Fighter::get_dir() const { return dir; }

Rectangle Fighter::get_body() const { return body; }

bool Fighter::on_ground() const { return ground.has_value(); }

void Fighter::hit(Attack &attack) {
  // Do nothing if invincible.
  if (iFrames >= 0) {
    return;
  }

  percentage += attack.get_damage();

  auto kb = attack.get_kb_vec(percentage);
  v.x = kb.x;
  v.y = kb.y;

  iFrames = 30;
}

void Fighter::set_action(Action _action) {
  if (_action != action) {
    action = _action;
    aFrames = 0;
  }
}

void Fighter::default_update(Game &game) {
  bool left = IsKeyDown(leftKey);
  bool right = IsKeyDown(rightKey);
  bool jump = IsKeyDown(jumpKey);

  handle_movement(left, right, jump);
  handle_oob();
  handle_collision(game.get_stage());
  handle_attacks(game.get_attacks());
  handle_action(left, right);

  cooldown--;
  iFrames--;
  aFrames++;
}

void Fighter::update(Game &game) { default_update(game); }

void Fighter::set_cooldown(int32_t _cooldown) { cooldown = _cooldown; }

bool Fighter::can_attack() const { return cooldown < 0; }

void Fighter::handle_movement(bool left, bool right, bool jump) {
  // Horizontal movement.
  if (can_attack()) {
    if (left) {
      v.x -= std::clamp(v.x - -maxSpeedH, 0.0f, acceleration);
      dir = Dir::LEFT;
    }
    if (right) {
      v.x += std::clamp(maxSpeedH - v.x, 0.0f, acceleration);
      dir = Dir::RIGHT;
    }
  }

  // Deccelerate if no key is pressed.
  if (!can_attack() || (!left && !right)) {
    if (std::abs(v.x) <= decceleration) {
      // Slowed down to a stop.
      v.x = 0.f;
    } else {
      // Deccelerate.
      v.x -= std::copysign(decceleration, v.x);
    }
  }

  // Vertical movement.
  if (IsKeyDown(jumpKey) && ground.has_value() && cooldown < 0) {
    v.y = -jumpSpeed;
    v.x += ground.value()->v.x;
  } else {
    v.y += GRAVITY;
  }

  // Limit player speed.
  v.y = std::min(v.y, 2.0f * maxSpeedH);
}

void Fighter::handle_oob() {
  bool oob = body.x <= -body.width || body.x >= WIN_W || body.y >= WIN_H;

  if (oob) {
    std::cout << "Respawning from OOB" << std::endl;
    respawn();
  }
}

void Fighter::handle_collision(Stage &stage) {
  float x = body.x + v.x;
  float y = body.y + v.y;
  bool hitX, hitY = false;

  // If on a tile, move with it.
  if (ground.has_value()) {
    auto floor = ground.value();
    x += floor->v.x;
  }

  ground = std::nullopt;

  for (auto &tile : stage.get_tiles()) {
    // Horizontal collision check.
    auto testBody = Rectangle(x, body.y, body.width, body.height);
    auto pre = tile;
    pre.body.y -= tile.v.y;
    if (CheckCollisionRecs(testBody, tile.body) &&
        CheckCollisionRecs(testBody, pre.body)) {
      // Check if crushed (collided twice).
      if (hitX) {
        std::cout << "Respawning from x squish" << std::endl;
        respawn();
        return;
      } else {
        hitX = true;
      }

      if (v.x > 0.0f) {
        // Both moving right, tile faster:
        if (tile.v.x > v.x) {
          x = tile.body.x + tile.body.width;
          v.x = tile.v.x;
        } else {
          x = tile.body.x - body.width;
          v.x = 0.0f;
        }
      } else if (v.x < 0.0f) {
        // Both moving left, tile faster:
        if (tile.v.x < v.x) {
          x = tile.body.x - body.width;
          v.x = tile.v.x;
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
      // Check if crushed (collided twice).
      if (hitY) {
        std::cout << "Respawning from y squish" << std::endl;
        respawn();
        return;
      } else {
        hitY = true;
      }

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

void Fighter::handle_attacks(std::list<std::unique_ptr<Attack>> &attacks) {
  // If can't attack now, nothing to be done.
  if (!can_attack()) {
    return;
  }

  if (IsKeyDown(attackKey)) {
    if (on_ground()) {
      attacks.push_back(ground_attack());
    } else {
      attacks.push_back(air_attack());
    }
  }
}

void Fighter::handle_action(bool left, bool right) {
  if (ground.has_value()) {
    if (cooldown > 0) {
      set_action(Action::GROUND_ATTACK);
    } else if (left != right) {
      set_action(Action::WALK);
    } else {
      set_action(Action::IDLE);
    }
  } else {
    if (cooldown > 0) {
      set_action(Action::AIR_ATTACK);
    } else {
      set_action(Action::JUMP);
    }
  }
}
