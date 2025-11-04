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

  // The attack's current damage.
  float dmg;

  // The attack's current body.
  Rectangle body;

  // The attack's age in ticks.
  uint32_t ticks;

public:
  virtual ~Attack() = default;

  /**
   * Checks for and handles collision between the fighters.
   */
  void handle_collision(std::vector<std::unique_ptr<Fighter>> &fighters);

  /**
   * The attack's damage value.
   *
   * @return The attack's damage
   */
  float get_dmg() const;

  /**
   * The attack's knockback value.
   *
   * @return The attack's knockback
   */
  Vector2 get_kb() const;

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

  /**
   * The attack's on-hit callback.
   *
   * By default, this function just knocks the hit fighter back.
   *
   * @param p The fighter that was hit
   */
  virtual void on_hit(Fighter &p);

  /**
   * Returns `true` if the attack is active and able to hit, `false` if not.
   */
  virtual bool is_active() const;

  /**
   * Returns `true` if the attack is finished and should be deleted, `false` if
   * not.
   */
  virtual bool is_done() const;

protected:
  Attack(Fighter *src, Vector2 kb, float damage, Rectangle body);

  /**
   * Default udpate function.
   *
   * Just increments the `.ticks`.
   */
  void default_update();
};
