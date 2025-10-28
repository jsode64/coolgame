#pragma once

#include "raylib.h"
#include "tile.hpp"

#include <tuple>
#include <vector>

class Stage {
private:
  /// @brief A collection of the stage's bodies.
  std::vector<Tile> tiles;

  /// @brief The stage's color.
  Color color;

public:
  Stage();

  /// @return Returns the test stage.
  static Stage test();
  static Stage stage_one();

  /**
   * Returns the stage's tile vector.
   */
  std::vector<Tile> &get_tiles();

  /// @brief Updates the stage's tiles.
  void update();

  /// @brief Draws the stage.
  void draw() const;
};
