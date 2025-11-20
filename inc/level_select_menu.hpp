#pragma once

#include <array>

class LevelSelectMenu {
private:
  std::array<const char *, 5> options;
  size_t choice;
  bool selected;

public:
  LevelSelectMenu();

  /** @brief Returns `true` if a stage has been chosen, `false` if not. */
  bool choice_made() const;

  /** @brief Returns the stage choise. */
  size_t get_choice() const;

  /** @brief Updates the level select menu. */
  void update();

  /** @brief Draws the level select menu. */
  void draw() const;
};
