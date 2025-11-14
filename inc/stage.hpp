#pragma once

#include "raylib.h"
#include "tile.hpp"

#include <memory>
#include <vector>

class Stage {
private:
  /** @brief Vector of tiles */
  std::vector<std::unique_ptr<Tile>> tiles;

  /** @brief Tile color */
  Color color;

public:
  Stage();

  /** @brief The test stage. */
  static Stage test();

  /** @brief Stage one. */
  static Stage stage_one();

  /** @brief Returns a vector of the stage's tiles. */
  std::vector<std::unique_ptr<Tile>>& get_tiles();

  /** @brief Updates the stage's tiles. */
  void update();

  /** @brief Draws the stage's tiles. */
  void draw() const;
};
