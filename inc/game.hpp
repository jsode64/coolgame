#pragma once

#include <memory>
#include <vector>

#include "attack.hpp"
#include "fighter.hpp"
#include "game.hpp"
#include "pausemenu.hpp"
#include "openingmenu.hpp"
#include "levelmenu.hpp"
#include "stage.hpp"
#include <iostream>

class Attack;
class Fighter;

class PauseMenu;
class OpeningMenu;
class LevelMenu;

enum class State {
  Opening,
  LevelSelect,
  Playing,
  Pause,
  GameOver,
  };

class Game {
private:
  Stage stage;
  std::vector<std::unique_ptr<Fighter>> fighters;
  std::vector<std::unique_ptr<Attack>> attacks;

public:
  State currentState; 
  //void handleState();

  Game();

  /**
   * Updates the game state.
   */
  void update();

  void handle_state(LevelMenu& level, OpeningMenu& opening, PauseMenu& paused);

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

  void changeState(State newState);
};
