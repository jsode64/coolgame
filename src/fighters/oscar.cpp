#include "fighters/oscar.hpp"
#include "attack.hpp"

class OscarGroundAttack : public Attack {
public:
  OscarGroundAttack(Fighter *src)
      : Attack(src, Vector2(0.0f, -0.5f), src->get_body()) {}
};

class OscarAirAttack : public Attack {
public:
  OscarAirAttack(Fighter *src)
      : Attack(src, Vector2(0.0f, -0.5f), src->get_body()) {}
};

Oscar::Oscar(int32_t leftKey, int32_t rightKey, int32_t jumpKey,
             int32_t attackKey)
    : Fighter(Rectangle(0.0f, 0.0f, 50.0f, 50.0f), 10.0f, ACCELERATION,
              DECCELERATION, MAX_SPEED, leftKey, rightKey, jumpKey, attackKey) {
}

void Oscar::draw() const { DrawRectangleRec(body, RED); }

std::unique_ptr<Attack> Oscar::ground_attack() {
  return std::make_unique<OscarGroundAttack>(this);
}

std::unique_ptr<Attack> Oscar::air_attack() {
  return std::make_unique<OscarAirAttack>(this);
}
