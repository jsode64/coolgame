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

class Fighter {
protected:
  Rectangle body;
  Vector2 v;

  float jumpSpeed;
  float acceleration;
  float decceleration;
  float maxSpeedH;

  std::optional<const Tile *> ground;

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
  void respawn(Stage &stage);

  /**
   * Returns the fighter's body.
   */
  Rectangle get_body() const;

  /**
   * Returns true if the fighter is on the ground, false if not.
   */
  bool on_ground() const;

  /**
   * Applies the knockback to the fighter.
   */
  void knock_back(Vector2 kb);

  /**
   * Updates the fighter.
   *
   * @param game The game state to be used
   */
  void update(Game &game);

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
   * Handles fighter movement via user input.
   */
  void handle_movement();

  /**
   * Handles player being OOB (out of bounds).
   * @param stage The stage blastzone size
   */
  void handle_oob(Stage &stage);

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
