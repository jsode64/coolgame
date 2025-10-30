#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

#include "raylib.h"

class Attack;
class Game;
class Tile;
class Stage;

enum class Dir {
  LEFT = 1,
  RIGHT = -1,
};

enum class Action {
  IDLE,
  WALK,
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

  std::optional<const Tile *> ground;

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
   * The default update function for the fighter.
   *
   * Handles input, movement, and collision.
   *
   * @param game The game state to be used
   */
  void default_update(Game &game);

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
   * Returns `true` if a ground attack can be used.
   *
   * By default, returns `true` always.
   *
   * @return Is `true` if can attack, `false` if not.
   */
  virtual bool can_ground_attack() const;

  /**
   * Returns `true` if an air attack can be used.
   *
   * By default, returns `true` always.
   *
   * @return Is `true` if can attack, `false` if not.
   */
  virtual bool can_air_attack() const;

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
   * Handles fighter movement via user input.
   */
  void handle_movement();

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
  void handle_attacks(std::vector<std::unique_ptr<Attack>> &attacks);
};
