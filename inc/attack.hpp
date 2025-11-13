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

  // The attack's current body.
  Rectangle body;

  // The attack's age in ticks.
  uint32_t ticks;

  // The attack's knockback angle's x factor.
  float kx;

  // The attack's knockback angle's y factor.
  float ky;

  // The attack's damage.
  float d;

  // The attack's base knockback.
  float k;

  // The attack's knockback growth.
  float g;

public:
  virtual ~Attack() = default;

  /**
   * Checks for and handles collision between the fighters.
   */
  void handle_collision(std::vector<std::unique_ptr<Fighter>> &fighters);

  /**
   * Returns the attack's damage.
   * 
   * @return The attack's damage.
   */
  float get_damage() const;


  /**
   * The attack's knockback vector.
   * 
   * @param p The target's percent.
   *
   * @return The attack's knockback
   */
  Vector2 get_kb_vec(float p) const;

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
  Attack(Fighter *src, Rectangle body, float angle, float d, float k, float g);
};
