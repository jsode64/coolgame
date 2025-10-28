#include "fighters/oscar.hpp"

#include "assets.hpp"
#include "attack.hpp"

class OscarGroundAttack : public Attack {
private:
  float vx;
  bool done;

public:
  OscarGroundAttack(Fighter *src)
      : Attack(src, Vector2(0.f, -5.f), 1.f, src->get_body()), done(false) {
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

class OscarAirAttack : public Attack {
public:
  OscarAirAttack(Fighter *src)
      : Attack(src, Vector2(0.0f, -0.5f), 10.0f, src->get_body()) {}

  bool is_done() const override { return true; }
};

Oscar::Oscar(int32_t leftKey, int32_t rightKey, int32_t jumpKey,
             int32_t attackKey)
    : Fighter(Rectangle(0.0f, 0.0f, 50.0f, 50.0f), 10.0f, ACCELERATION,
              DECCELERATION, MAX_SPEED, leftKey, rightKey, jumpKey, attackKey) {
  respawn();
}

void Oscar::update(Game &game) {
  groundCd--;
  airCd--;

  default_update(game);
}

void Oscar::draw() const {
  DrawTexturePro(Assets::FOO,
                 Rectangle(0, 0,
                           Assets::FOO.width * ((dir == Dir::LEFT) ? 1 : -1),
                           Assets::FOO.height),
                 body, Vector2(0.0f, 0.0f), 0.0f, WHITE);
}

bool Oscar::can_ground_attack() const { return groundCd < 1; }

std::unique_ptr<Attack> Oscar::ground_attack() {
  groundCd = 60;
  return std::make_unique<OscarGroundAttack>(this);
}

std::unique_ptr<Attack> Oscar::air_attack() {
  return std::make_unique<OscarAirAttack>(this);
}
