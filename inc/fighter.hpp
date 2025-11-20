#pragma once

#include <cstdint>
#include <list>
#include <memory>
#include <optional>
#include <vector>

#include "raylib.h"

class Attack;
class Game;
class Tile;
class Stage;

enum class Dir {
  LEFT = -1,
  RIGHT = 1,
};

enum class Action {
  IDLE,
  WALK,
  JUMP,
  GROUND_ATTACK,
  AIR_ATTACK,
};

class Fighter {
protected:
  Rectangle body;
  Vector2 v;

  float jumpSpeed;
  float acceleration;
  float decceleration;
  float maxSpeedH;
  Dir dir;

  float percentage;
  int32_t iFrames;
  int32_t cooldown;

  bool hasDoubleJump;
  std::optional<std::unique_ptr<Tile> *> ground;

  Action action;
  uint32_t aFrames;

  int32_t leftKey;
  int32_t rightKey;
  int32_t jumpKey;
  int32_t attackKey;

public:
  Fighter(Rectangle body, float jumpSpeed, float acceleration,
          float decceleration, float maxSpeedH, int32_t leftKey,
          int32_t rightKey, int32_t jumpKey, int32_t attackKey);

  virtual ~Fighter() = default;

  /**
   * Respawns the fighter.
   */
  void respawn();

  /**
   * Returns the fighter's direction.
   */
  Dir get_dir() const;

  /**
   * Returns the fighter's body.
   */
  Rectangle get_body() const;

  /** @brief Returns the fighter's velocity. */
  Vector2 get_v() const;

  /**
   * Returns true if the fighter is on the ground, false if not.
   */
  bool on_ground() const;

  /**
   * Hits the player with the given attack.
   *
   * If the player has invincibility frames, does nothing.
   */
  void hit(Attack &attack);

  /**
   * Sets the action to the given one.
   *
   * If the action is different than the current one, resets the action frames.
   *
   * @param action The action to be used.
   */
  void set_action(Action action);

  /**
   * Updates the fighter.
   *
   * By default calls `Fighter::default_update`, which should be called anway.
   *
   * @param game The game state to be used
   */
  virtual void update(Game &game);

  /**
   * Draws the fighter.
   */
  virtual void draw() const = 0;

  /**
   * Returns a new ground attack.
   */
  virtual std::unique_ptr<Attack> ground_attack() = 0;

  /**
   * Returns a new air attack.
   */
  virtual std::unique_ptr<Attack> air_attack() = 0;

protected:
  /**
   * Sets the attack cooldown.
   */
  void set_cooldown(int32_t cooldown);

  /**
   * Returns `true` if the attack cooldown is over, `false` if not.
   */
  bool can_attack() const;

private:
  /**
   * Handles fighter movement via user input.
   */
  void handle_movement(bool left, bool right, bool jump);

  /**
   * Handles player being OOB (out of bounds).
   */
  void handle_oob();

  /**
   * Handles player collision.
   *
   * @param stage The stage to collide with
   */
  void handle_collision(Stage &stage);

  /**
   * Handles the fighter using an attack.
   */
  void handle_attacks(std::list<std::unique_ptr<Attack>> &attacks);

  /**
   * Handles the fighter action state.
   */
  void handle_action(bool left, bool right);
};
