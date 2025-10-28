#pragma once

#include <memory>
#include <vector>

#include "attack.hpp"
#include "fighter.hpp"
#include "stage.hpp"
#include "gamepad.hpp"

class Attack;
class Fighter;

class Game {
private:
  Stage stage;
  std::vector<std::unique_ptr<Fighter>> fighters;
  std::vector<std::unique_ptr<Attack>> attacks;
  Gamepad input1;

public:
  Game();

  /**
   * Updates the game state.
   */
  void update();

  /**
   * Draws the game.
   */
  void draw() const;

  /**
   * Returns the game's stage.
   */
  Stage &get_stage();

  /**
   * Returns the game's fighters.
   */
  std::vector<std::unique_ptr<Fighter>> &get_fighters();

  /**
   * Returns the game's attacks.
   */
  std::vector<std::unique_ptr<Attack>> &get_attacks();

  /**
   * Pushes the attack to the game state.
   *
   * @param attack The attack to be pushed
   */
  void push_attack(std::unique_ptr<Attack> atk);
};
