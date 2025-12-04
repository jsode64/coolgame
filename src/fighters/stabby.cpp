#include "fighters/stabby.hpp"

#include "assets.hpp"
#include "attack.hpp"
#include "util.hpp"

class StabbyGroundAttack : public Attack {
private:
  constexpr static float W = 64.f;
  constexpr static float H = 34.f;

public:
  StabbyGroundAttack(Fighter *src)
      : Attack(src, src->get_body(), 30.f * DEG2RAD, 15.f, 15.f, 1.2f) {
    body = calc_body();
  }

  void update(Game &game) override {
    body = calc_body();

    Attack::update(game);
  }

  void draw() const override {
    if (is_active()) {
      DrawRectangleRec(rect_to_win(body), Color(255, 0, 0, 128));
    }
  }

  bool is_active() const override { return ticks >= 8 && ticks < 16; }

  bool is_done() const override { return ticks > 32; }

private:
  Rectangle calc_body() {
    auto body = src->get_body();
    float x = body.x + (body.width / 2.f);
    float y = body.y + (body.height / 2.f);

    if (src->get_dir() == Dir::LEFT) {
      body = Rectangle(x - W, y - (H / 2.f), W, H);
    } else {
      body = Rectangle(x, y - (H / 2.f), W, H);
    }

    return body;
  }
};

class StabbyAirAttack : public Attack {
private:
  constexpr static float W = 16.f;
  constexpr static float H = 54.f;

public:
  StabbyAirAttack(Fighter *src)
      : Attack(src, src->get_body(), -90.f * DEG2RAD, 8.f, 20.f, 0.2f) {
    body = calc_body();
  }

  void update(Game &game) override {
    body = calc_body();

    Attack::update(game);
  }

  void draw() const override {
    if (is_active()) {
      DrawRectangleRec(rect_to_win(body), Color(255, 0, 0, 128));
    }
  }

  bool is_active() const override { return ticks >= 16 && ticks < 32; }

  bool is_done() const override { return ticks > 32 || src->on_ground(); }

private:
  Rectangle calc_body() {
    auto body = src->get_body();
    float x = body.x + (body.width / 2.f);
    float y = body.y + (body.height / 2.f);

    if (src->get_dir() == Dir::LEFT) {
      body = Rectangle(x - W, y, W, H);
    } else {
      body = Rectangle(x, y, W, H);
    }

    return body;
  }
};

Stabby::Stabby(int32_t leftKey, int32_t rightKey, int32_t jumpKey,
               int32_t attackKey)
    : Fighter(Rectangle(0.f, 0.f, 20.f, 48.f), 15.f, ACCELERATION,
              DECCELERATION, MAX_SPEED, leftKey, rightKey, jumpKey, attackKey) {
  spawn();
}

void Stabby::draw() const {
  Rectangle src = Rectangle(0.f, 0.f, 32.f, 32.f);
  Rectangle dst = Rectangle(body.x - 22.f, body.y - 16.f, 64.f, 64.f);
  Texture2D tex = {0};

  if (action == Action::IDLE) {
    src.x = 32.f * float((aFrames % 64) / 8);
    tex = Assets::STABBY_IDLE;
  } else if (action == Action::WALK) {
    src.x = 32.f * float((aFrames % 64) / 8);
    tex = Assets::STABBY_WALK;
  } else if (action == Action::JUMP) {
    tex = Assets::STABBY_JUMP;
  } else if (action == Action::GROUND_ATTACK) {
    dst.width = 96.f;
    if (dir == Dir::LEFT) {
      dst.x -= 32.f;
    }
    src.x = 48.f * float((aFrames % 64) / 8);
    src.width = 48.f;
    tex = Assets::STABBY_SWING;
  } else if (action == Action::AIR_ATTACK) {
    src.x = 32.f * float((aFrames % 64) / 8);
    src.height = 48.f;
    dst.height = 96.f;
    tex = Assets::STABBY_AIR_ATTACK;
  }

  src.width *= float(dir);
  DrawTexturePro(tex, src, rect_to_win(dst), Vector2(0.f, 0.f), 0.f,
                 Color(225, 150, 150, 255));
  DrawRectangleRec(body, Color(0, 0, 0, 128));
}

std::unique_ptr<Attack> Stabby::ground_attack() {
  set_cooldown(32);
  return std::make_unique<StabbyGroundAttack>(this);
}

std::unique_ptr<Attack> Stabby::air_attack() {
  set_cooldown(32);
  return std::make_unique<StabbyAirAttack>(this);
}
