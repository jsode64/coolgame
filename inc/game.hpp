#pragma once

#include <list>
#include <memory>
#include <vector>

#include "attack.hpp"
#include "fighter.hpp"
#include "game.hpp"
#include "level_select_menu.hpp"
#include "main_menu.hpp"
#include "stage.hpp"

class Attack;
class Fighter;

enum class State {
  Open,
  LevelSelect,
  Play,
};

class LevelSelectMenu;

class Game {
private:
  State state;

  // Game state values:

  Stage stage;
  std::vector<std::unique_ptr<Fighter>> fighters;
  std::list<std::unique_ptr<Attack>> attacks;

  // Menu states:

  MainMenu main_menu;
  LevelSelectMenu level_select_menu;

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
  std::list<std::unique_ptr<Attack>> &get_attacks();

private:
  /** @brief Updates the game during play. */
  void update_play();

  /** @brief Initializes the play state to the given stage index. */
  void init_play(size_t i);
};
