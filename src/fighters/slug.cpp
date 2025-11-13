#include "fighters/slug.hpp"

#include "assets.hpp"
#include "attack.hpp"
#include "util.hpp"
#include "gamepad.hpp"

class SlugGroundAttack : public Attack {
private:
  float vx;
  bool done;

public:
  SlugGroundAttack(Fighter *src)
      : Attack(src, src->get_body(), 90.*DEG2RAD, 10., 4., 2.), done(false) {
    vx = src->get_dir() == Dir::LEFT ? -1.f : 1.f;
  }

  void update(Game &game) override {
    body.x += vx;

    // End attack if collided with anything.
    for (const auto &tile : game.get_stage().get_tiles()) {
      if (CheckCollisionRecs(body, tile.body)) {
        done = true;
        break;
      }
    }
  }

  void draw() const override { DrawRectangleRec(body, BROWN); }

  bool is_done() const override { return done; }
};

void Slug::default_update(Game &game) {
  bool left = (IsKeyDown(leftKey) || IsGamepadButtonDown(controller.portReturn(), GAMEPAD_BUTTON_LEFT_FACE_LEFT));
  bool right = (IsKeyDown(rightKey)  || IsGamepadButtonDown(controller.portReturn(), GAMEPAD_BUTTON_LEFT_FACE_RIGHT));
  bool jump = (IsKeyDown(jumpKey) || IsGamepadButtonDown(controller.portReturn(), GAMEPAD_BUTTON_RIGHT_FACE_UP));

  handle_movement(left, right, jump);
  handle_oob();
  handle_collision(game.get_stage());
  handle_attacks(game.get_attacks());
  handle_action(left, right);

  cooldown--;
  iFrames--;
  aFrames++;
}

void Slug::handle_attacks(std::list<std::unique_ptr<Attack>> &attacks) {
  // If can't attack now, nothing to be done.
  if (!can_attack()) {
    return;
  }

  if (IsKeyDown(attackKey) || IsGamepadButtonDown(controller.portReturn(), GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) {
    if (on_ground()) {
      attacks.push_back(ground_attack());
    } else {
      attacks.push_back(air_attack());
    }
  }
}

class SlugAirAttack : public Attack {
public:
  SlugAirAttack(Fighter *src)
      : Attack(src, src->get_body(), 90.*DEG2RAD, 10., 4., 2.) {}

  bool is_done() const override { return true; }
};

Slug::Slug(int32_t leftKey, int32_t rightKey, int32_t jumpKey,
           int32_t attackKey, Gamepad controller)
    : Fighter(Rectangle(0.0f, 0.0f, 50.0f, 50.0f), 10.0f, ACCELERATION,
              DECCELERATION, MAX_SPEED, leftKey, rightKey, jumpKey, attackKey, controller) {
  respawn();
}

void Slug::update(Game &game) {
  groundCd--;
  airCd--;

  default_update(game);
}

void Slug::draw() const {
  if (action == Action::WALK) {
    DrawRectangleRec(rect_to_win(body), BROWN);
  } else {
    auto tick = (aFrames % 60) / 15;
    float x = tick == 3 ? 32.f : float(tick * 32);
    DrawTexturePro(Assets::SLUG_IDLE,
                   Rectangle(x, 0.f, 32.f * float(dir), 32.f), rect_to_win(body),
                   Vector2(0.f, 0.f), 0.f, BROWN);
  }
}

std::unique_ptr<Attack> Slug::ground_attack() {
  groundCd = 60;
  return std::make_unique<SlugGroundAttack>(this);
}

std::unique_ptr<Attack> Slug::air_attack() {
  return std::make_unique<SlugAirAttack>(this);
}
