#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "raylib.h"

#include "fighter.hpp"
#include "game.hpp"

class Fighter;
class Game;

class Attack {
protected:
  // The fighter the attack came from.
  Fighter *src;

  // The attack's current knockback.
  Vector2 kb;

  // The attack's current body.
  Rectangle body;

public:
  virtual ~Attack() = default;

  // TODO: `.is_done` to delete finished attacks.

  /**
   * Checks for and handles collision between the fighters.
   */
  void handle_collision(std::vector<std::unique_ptr<Fighter>> &fighters);

  /**
   * The attack's update function.
   *
   * By default, this function does nothing.
   */
  virtual void update(Game &game);

  /**
   * The attack's draw/render function.
   *
   * By default this function does nothing and renders norhing.
   */
  virtual void draw() const;

protected:
  Attack(Fighter *src, Vector2 kb, Rectangle body);

  /**
   * The attack's on-hit callback.
   *
   * By default, this function just knocks the hit fighter back.
   *
   * @param p The fighter that was hit
   */
  virtual void on_hit(Fighter &p);
};
