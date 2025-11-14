#include "attack.hpp"

#include <cmath>

Attack::Attack(Fighter *src, Rectangle body, float angle, float d, float k, float g)
    : src(src), body(body), ticks(0), kx(std::cos(angle) * float(src->get_dir())), ky(-std::sin(angle)), d(d), k(k), g(g) {}

void Attack::handle_collision(std::vector<std::unique_ptr<Fighter>> &fighters) {
  // If the attack is inactive there's no need to check.
  if (!is_active()) {
    return;
  }

  for (auto &fighter : fighters) {
    // Catch hitting own fighter.
    if (fighter.get() == src) {
      continue;
    }

    if (CheckCollisionRecs(body, fighter->get_body())) {
      on_hit(*fighter);
    }
  }
}

void Attack::update(Game &_) {
  ticks++;
}

void Attack::on_hit(Fighter &f) { f.hit(*this); }

void Attack::draw() const {}

float Attack::get_damage() const {
  return d;
}

Vector2 Attack::get_kb_vec(float p) const {
  float m = k + (p * g / 100.);

  return Vector2(kx * m, ky * m);
}

bool Attack::is_active() const { return true; }

bool Attack::is_done() const { return false; }
