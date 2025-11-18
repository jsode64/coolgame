#include "fighter.hpp"
#include "attack.hpp"
#include "game.hpp"
#include "stage.hpp"
#include "tile.hpp"

#include <algorithm>
#include <cmath>

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

  hasDoubleJump = false;
  ground = std::nullopt;
}

void Fighter::respawn() {
  body.x = (float(SIM_W) - body.width) / 2.f;
  body.y = (float(SIM_H) - body.height) / 2.f;

  v = Vector2(0.0f, 0.0f);

  ground = std::nullopt;

  percentage = 0.f;
}

Dir Fighter::get_dir() const { return dir; }

Rectangle Fighter::get_body() const { return body; }

Vector2 Fighter::get_v() const { return v; }

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

void Fighter::update(Game &game) {
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

  // Pause.
  if (IsKeyDown(KEY_P))
    game.currentState = State::Pause;
}

void Fighter::set_cooldown(int32_t _cooldown) { cooldown = _cooldown; }

bool Fighter::can_attack() const { return cooldown < 0; }

void Fighter::handle_movement(bool left, bool right, bool jump) {
  // Horizontal movement.
  if (can_attack()) {
    if (left) {
      v.x -= std::clamp(v.x - -maxSpeedH, 0.f, acceleration);
      dir = Dir::LEFT;
    }
    if (right) {
      v.x += std::clamp(maxSpeedH - v.x, 0.f, acceleration);
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
  if (IsKeyPressed(jumpKey) && (ground.has_value() || hasDoubleJump) && cooldown < 0) {
    v.y = -jumpSpeed;
    if (on_ground()) {
      v.x += (*ground.value())->get_v().x;
    } else {
      hasDoubleJump = false;
    }
  } else {
    v.y += GRAVITY;
  }

  // Limit player speed.
  v.y = std::min(v.y, 2.0f * maxSpeedH);
}

void Fighter::handle_oob() {
  bool oob = body.x <= -body.width || body.x >= SIM_W || body.y >= SIM_H;

  if (oob) {
    respawn();
  }
}

void Fighter::handle_collision(Stage &stage) {
  float x = body.x + v.x;
  float y = body.y + v.y;

  /* Tracking squishing. Each is tracking if hit from that direction, for
  example, `hitDown` will be true when hit from below (landing/standing) */
  bool hitUp = false;
  bool hitDown = false;
  bool hitLeft = false;
  bool hitRight = false;

  // If on a tile, move with it.
  if (ground.has_value()) {
    x += (*ground.value())->get_v().x;
  }

  ground = std::nullopt;

  for (auto &tile : stage.get_tiles()) {
    // Horizontal collision check.
    auto tileBody = tile->get_body();
    auto tileV = tile->get_v();
    auto testBody = Rectangle(x, body.y, body.width, body.height);
    auto pre = tileBody;
    pre.y -= tileV.y;
    if (CheckCollisionRecs(testBody, tileBody) &&
        CheckCollisionRecs(testBody, pre)) {
      if (v.x > 0.0f) {
        if (tileV.x > v.x) {
          // Both moving right, tile faster:
          x = tileBody.x + tileBody.width;
          v.x = tileV.x;
          hitLeft = true;
        } else {
          x = tileBody.x - body.width;
          v.x = 0.0f;
          hitRight = true;
        }
      } else if (v.x < 0.0f) {
        if (tileV.x < v.x) {
          // Both moving left, tile faster:
          x = tileBody.x - body.width;
          v.x = tileV.x;
          hitRight = true;
        } else {
          x = tileBody.x + tileBody.width;
          v.x = 0.0f;
          hitLeft = true;
        }
      } else {
        // Player not moving, tile must have hit them.
        if (tileV.x > 0.0f) {
          x = tileBody.x + tileBody.width;
          hitLeft = true;
        } else {
          x = tileBody.x - body.width;
          hitRight = true;
        }
        v.x += tileV.x;
      }
    }

    // Vertical collision check.
    testBody = Rectangle(x, y, body.width, body.height);
    if (CheckCollisionRecs(testBody, tileBody)) {
      if (v.y >= 0.0f) {
        y = tileBody.y - body.height;

        // On ground.
        hasDoubleJump = true;
        ground.emplace(&tile);
        tile->stood_on();
        hitDown = true;
      } else {
        y = tileBody.y + tileBody.height;
        hitUp = true;
      }
      v.y = 0;
    }

      // Check for squish.
      if ((hitLeft && hitRight) || (hitUp && hitDown)) {
        respawn();
        return;
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
  if (cooldown == 0) {
    if (action == Action::AIR_ATTACK) {
      set_action(Action::JUMP);
    } else {
      set_action(Action::IDLE);
    }
  } else if (ground.has_value()) {
    if (left != right) {
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
