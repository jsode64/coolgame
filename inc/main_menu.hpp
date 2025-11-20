#pragma once

class MainMenu {
private:
  bool selected;

public:
  MainMenu();

  /** @brief Returns `true` if the user(s) passed the main menu, `false` if not. */
  bool was_passed() const;

  /** @brief Updates the main menu's state. */
  void update();

  /** @brief Draws the main menu. */
  void draw() const;
};
