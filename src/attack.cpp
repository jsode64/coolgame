#include "attack.hpp"

Attack::Attack(Fighter *src, Vector2 kb, Rectangle body)
    : src(src), kb(kb), body(body) {}

void Attack::handle_collision(std::vector<std::unique_ptr<Fighter>> &fighters) {
  for (auto &fighter : fighters) {
    // Don't hit a fighter with their own attack.
    if (fighter.get() == src) {
      continue;
    }

    if (CheckCollisionRecs(body, fighter->get_body())) {
      on_hit(*fighter);
    }
  }
}

void Attack::update(Game &_) {}

void Attack::on_hit(Fighter &f) { f.knock_back(kb); }

void Attack::draw() const {}