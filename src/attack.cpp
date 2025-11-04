#include "attack.hpp"

Attack::Attack(Fighter *src, Vector2 kb, float dmg, Rectangle body)
    : src(src), kb(kb), dmg(dmg), body(body), ticks(0) {}

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

void Attack::update(Game &_) {}

void Attack::on_hit(Fighter &f) { f.hit(*this); }

void Attack::draw() const {}

float Attack::get_dmg() const { return dmg; }

Vector2 Attack::get_kb() const { return kb; }

bool Attack::is_active() const { return true; }

bool Attack::is_done() const { return false; }

void Attack::default_update() { ticks++; }
