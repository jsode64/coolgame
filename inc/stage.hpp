#pragma once

#include <memory>
#include <vector>

#include "raylib.h"

#include "tile.hpp"

class Stage {
private:
  /** @brief Vector of tiles. */
  std::vector<std::unique_ptr<Tile>> tiles;

  /** @brief Background sprite. */
  Texture2D bg;

  /** @brief Tile color. */
  Color color;

public:
  Stage(Texture2D bg, Color color);

  /** @brief Stage one: Destination. */
  static Stage stage_one();

  /** @brief Stage two: Pillars. */
  static Stage stage_two();

  /** @brief Stage three: Crush. */
  static Stage stage_three();

  /** @brief Stage foour: Slop. */
  static Stage stage_four();

  /** @brief Stage five: Sky. */
  static Stage stage_five();

  /** @brief Returns a vector of the stage's tiles. */
  std::vector<std::unique_ptr<Tile>> &get_tiles();

  /** @brief Updates the stage's tiles. */
  void update();

  /** @brief Draws the stage's tiles. */
  void draw() const;
};
