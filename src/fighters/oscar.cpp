#include "fighters/oscar.hpp"

#include "assets.hpp"
#include "attack.hpp"
#include "util.hpp"

class OscarGroundAttack : public Attack {
private:
  float vx;
  bool done;

public:
  OscarGroundAttack(Fighter *src)
      : Attack(src, src->get_body(), 90. * DEG2RAD, 10., 30., 2.), done(false) {
    vx = src->get_dir() == Dir::LEFT ? -1.f : 1.f;
  }

  void update(Game &game) override {
    body.x += vx;

    // End attack if collided with anything.
    for (const auto &tile : game.get_stage().get_tiles()) {
      if (CheckCollisionRecs(body, tile->get_body())) {
        done = true;
        break;
      }
    }
  }

  void draw() const override { DrawRectangleRec(body, BROWN); }

  bool is_done() const override { return done; }
};

class OscarAirAttack : public Attack {
public:
  OscarAirAttack(Fighter *src)
      : Attack(src, src->get_body(), 90. * DEG2RAD, 10., 4., 2.) {}

  bool is_done() const override { return true; }
};

Oscar::Oscar(int32_t leftKey, int32_t rightKey, int32_t jumpKey,
             int32_t attackKey)
    : Fighter(Rectangle(0.0f, 0.0f, 50.0f, 50.0f), 12.0f, ACCELERATION,
              DECCELERATION, MAX_SPEED, leftKey, rightKey, jumpKey, attackKey) {
  spawn();
}

void Oscar::update(Game &game) { Fighter::update(game); }

void Oscar::draw() const {
  if (action == Action::WALK) {
    float x = 32.f * float((aFrames % 48) / 6);
    DrawTexturePro(Assets::OSCAR_WALK,
                   Rectangle(x, 0.f, 32.f * float(dir), 32.f),
                   rect_to_win(body), Vector2(0.f, 0.f), 0.f, RED);
  } else {
    DrawTexturePro(Assets::OSCAR_WALK,
                   Rectangle(0.f, 0.f, 32.f * float(dir), 32.f),
                   rect_to_win(body), Vector2(0.f, 0.f), 0.f, BLUE);
  }
}

std::unique_ptr<Attack> Oscar::ground_attack() {
  return std::make_unique<OscarGroundAttack>(this);
}

std::unique_ptr<Attack> Oscar::air_attack() {
  return std::make_unique<OscarAirAttack>(this);
}
