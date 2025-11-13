#pragma once

#include <functional>

#include "raylib.h"

class Tile {
protected:
  Rectangle body;
  Vector2 v;

public:
  Tile(float x, float y, float w, float h);

  /**
   * Returns the tile's body.
   */
  Rectangle get_body() const;

  /**
   * Returns the tile's velocity.
   */
  Vector2 get_v() const;

  /**
   * Updates the tile.
   * 
   * By default, this does nothing.
   */
  virtual void update();

  /**
   * Called when the tile is stood on.
   * 
   * By default, this does nothing.
   */
  virtual void stood_on();
};
