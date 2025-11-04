#include "fighters/luie.hpp"

#include "assets.hpp"
#include "attack.hpp"

class LuieGroundAttack : public Attack {
private:
  constexpr static float W = 64.f;
  constexpr static float H = 34.f;

public:
  LuieGroundAttack(Fighter *src)
      : Attack(src, Vector2(8.f * float(src->get_dir()), -2.f), 5.0f,
               src->get_body()) {
    auto srcBody = src->get_body();
    float x = srcBody.x + (srcBody.width / 2.f);
    float y = srcBody.y + (srcBody.height / 2.f);

    if (src->get_dir() == Dir::LEFT) {
      body = Rectangle(x - W, y - (H / 2.f), W, H);
    } else {
      body = Rectangle(x, y - (H / 2.f), W, H);
    }
  }

  void update(Game &_) override { default_update(); }

  void draw() const override {
    if (is_active()) {
      DrawRectangleRec(body, Color(255, 0, 0, 128));
    }
  }

  bool is_active() const override { return ticks > 8 && ticks < 16; }

  bool is_done() const override { return ticks > 30; }
};

class LuieAirAttack : public Attack {
public:
  LuieAirAttack(Fighter *src)
      : Attack(src, Vector2(0.0f, -0.5f), 1.0f, src->get_body()) {}

  bool is_done() const override { return true; }
};

Luie::Luie(int32_t leftKey, int32_t rightKey, int32_t jumpKey,
           int32_t attackKey, int32_t leftKeyController, int32_t rightKeyController, 
           int32_t jumpKeyController, int32_t attackKeyController)
    : Fighter(Rectangle(0.f, 0.f, 20.f, 48.f), 15.f, ACCELERATION,
              DECCELERATION, MAX_SPEED, leftKey, rightKey, jumpKey, attackKey, leftKeyController, rightKeyController, 
              jumpKeyController, attackKeyController) {
  respawn();
}

void Luie::draw() const {
  Rectangle src = Rectangle(0.f, 0.f, 32.f, 32.f);
  Rectangle dst = Rectangle(body.x - 12.f, body.y - 16.f, 64.f, 64.f);
  Texture2D tex = {0};

  if (action == Action::IDLE) {
    src.x = 32.f * float((aFrames % 64) / 8);
    tex = Assets::STABBY_IDLE;
  } else if (action == Action::WALK) {
    src.x = 32.f * float((aFrames % 64) / 8);
    tex = Assets::STABBY_WALK;
  } else if (action == Action::JUMP) {
    tex = Assets::STABBY_WALK;
  } else if (action == Action::GROUND_ATTACK) {
    dst.width = 96.f;
    if (dir == Dir::LEFT) {
      dst.x -= 32.f;
    }
    src.x = 48.f * float((aFrames % 64) / 8);
    src.width = 48.f;
    tex = Assets::STABBY_SWING;
  } else {
    DrawRectangleRec(body, GREEN);
  }

  src.width *= float(dir);
  DrawTexturePro(tex, src, dst, Vector2(0.f, 0.f), 0.f,
                 Color(225, 150, 150, 255));
}

std::unique_ptr<Attack> Luie::ground_attack() {
  set_cooldown(32);
  return std::make_unique<LuieGroundAttack>(this);
}

std::unique_ptr<Attack> Luie::air_attack() {
  set_cooldown(30);
  return std::make_unique<LuieAirAttack>(this);
}
