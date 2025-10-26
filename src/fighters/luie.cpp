#include "fighters/luie.hpp"
#include "attack.hpp"

class LuieGroundAttack : public Attack {
public:
  LuieGroundAttack(Fighter *src)
      : Attack(src, Vector2(0.0f, -0.5f), src->get_body()) {}

protected:
  void update(Game &_) override { body = src->get_body(); }
};

class LuieAirAttack : public Attack {
public:
  LuieAirAttack(Fighter *src)
      : Attack(src, Vector2(0.0f, -0.5f), src->get_body()) {}
};

Luie::Luie(int32_t leftKey, int32_t rightKey, int32_t jumpKey,
           int32_t attackKey)
    : Fighter(Rectangle(0.0f, 0.0f, 10.0f, 30.0f), 15.0f, ACCELERATION,
              DECCELERATION, MAX_SPEED, leftKey, rightKey, jumpKey, attackKey) {
}

void Luie::draw() const { DrawRectangleRec(body, GREEN); }

std::unique_ptr<Attack> Luie::ground_attack() {
  return std::make_unique<LuieGroundAttack>(this);
}

std::unique_ptr<Attack> Luie::air_attack() {
  return std::make_unique<LuieAirAttack>(this);
}
