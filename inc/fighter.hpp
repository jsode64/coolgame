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
  bool isAlive;

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

  /** @brief Hits the player with the given attack. */
  void hit(Attack &attack);

  /** @brief Spawns the fighter. */
  void spawn();

  /** @brief Returns the fighter's direction. */
  Dir get_dir() const;

  /** @brief Returns the player's body. */
  Rectangle get_body() const;

  /** @brief Returns the fighter's velocity. */
  Vector2 get_v() const;

  /** @brief Returns `true` if the fighter is alive, `false` if not. */
  bool is_alive() const;

  /** @brief Returns `true` if the fighter is on the ground, `false` if not. */
  bool on_ground() const;

  /** @brief Sets the action to the given one, or does nothing if already in that action. */
  void set_action(Action action);

  /** @brief Updates the fighter. */
  virtual void update(Game &game);

  /** @brief Draws the fighter. */
  virtual void draw() const = 0;

  /** @brief Returns a new instance of the fighter's ground attack. */
  virtual std::unique_ptr<Attack> ground_attack() = 0;

  /** @brief Returns a new instance of the fighter's air attack. */
  virtual std::unique_ptr<Attack> air_attack() = 0;

protected:
  /** @brief Sets the attack cooldown. */
  void set_cooldown(int32_t cooldown);

  /** @brief Returns `true` if the attack cooldown is over, `false` if not. */
  bool can_attack() const;

private:
  /** @brief Handles fighter movement via user input. */
  void handle_movement(bool left, bool right, bool jump);

  /** @brief Handles the fighter being out of bounds. */
  void handle_oob();

  /** @brief Handles fighter collision with the given stage. */
  void handle_collision(Stage &stage);

  /** @brief Handles the fighter's attacking state. */
  void handle_attacks(std::list<std::unique_ptr<Attack>> &attacks);

  /** @brief Handles the fighter's action state. */
  void handle_action(bool left, bool right);
};
