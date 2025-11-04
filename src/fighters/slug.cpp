#include "fighters/slug.hpp"

#include "assets.hpp"
#include "attack.hpp"

class SlugGroundAttack : public Attack {
private:
  float vx;
  bool done;

public:
  SlugGroundAttack(Fighter *src)
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

class SlugAirAttack : public Attack {
public:
  SlugAirAttack(Fighter *src)
      : Attack(src, Vector2(0.0f, -0.5f), 10.0f, src->get_body()) {}

  bool is_done() const override { return true; }
};

Slug::Slug(int32_t leftKey, int32_t rightKey, int32_t jumpKey,
           int32_t attackKey, int32_t leftKeyController, int32_t rightKeyController, 
             int32_t jumpKeyController, int32_t attackKeyController)
    : Fighter(Rectangle(0.0f, 0.0f, 50.0f, 50.0f), 10.0f, ACCELERATION,
              DECCELERATION, MAX_SPEED, leftKey, rightKey, jumpKey, attackKey, leftKeyController, rightKeyController, 
              jumpKeyController, attackKeyController) {
  respawn();
}

void Slug::update(Game &game) {
  groundCd--;
  airCd--;

  default_update(game);
}

void Slug::draw() const {
  if (action == Action::WALK) {

    DrawRectangleRec(body, BROWN);
  } else {
    auto tick = (aFrames % 60) / 15;
    float x = tick == 3 ? 32.f : float(tick * 32);
    DrawTexturePro(Assets::SLUG_IDLE,
                   Rectangle(x, 0.f, 32.f * float(dir), 32.f), body,
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
