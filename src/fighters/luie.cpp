#include "fighters/luie.hpp"
#include "attack.hpp"

class LuieGroundAttack : public Attack {
private:
  uint32_t ticks;

public:
  LuieGroundAttack(Fighter *src)
      : Attack(src, Vector2(0.0f, -0.5f), 5.0f, src->get_body()), ticks(0) {}

  void draw() const override { DrawRectangleRec(body, GRAY); }

  void update(Game &_) override {
    body = src->get_body();
    ticks++;
  }

  bool is_done() const override { return ticks > 30; }
};

class LuieAirAttack : public Attack {
public:
  LuieAirAttack(Fighter *src)
      : Attack(src, Vector2(0.0f, -0.5f), 1.0f, src->get_body()) {}

  bool is_done() const override { return true; }
};

Luie::Luie(int32_t leftKey, int32_t rightKey, int32_t jumpKey,
           int32_t attackKey)
    : Fighter(Rectangle(0.0f, 0.0f, 10.0f, 30.0f), 15.0f, ACCELERATION,
              DECCELERATION, MAX_SPEED, leftKey, rightKey, jumpKey, attackKey) {
  respawn();
}

void Luie::draw() const { DrawRectangleRec(body, GREEN); }

std::unique_ptr<Attack> Luie::ground_attack() {
  return std::make_unique<LuieGroundAttack>(this);
}

std::unique_ptr<Attack> Luie::air_attack() {
  return std::make_unique<LuieAirAttack>(this);
}
