#pragma once

#include "raylib.h"

class Assets {
public:
  static Texture2D FOO;

public:
  /**
   * Loads the assets.
   *
   * @return Is `false` if ANY texture fails to load.
   */
  static bool load();
};
