#pragma once

#include "raylib.h"

class Assets {
public:
  static Texture2D FOREST_BG;

  static Texture2D OSCAR_IDLE;
  static Texture2D OSCAR_WALK;

  static Texture2D STABBY_IDLE;
  static Texture2D STABBY_WALK;
  static Texture2D STABBY_SWING;
  static Texture2D STABBY_JUMP;
  static Texture2D STABBY_AIR_ATTACK;

  static Texture2D SLUG_IDLE;

public:
  /**
   * Loads the assets.
   *
   * @return Is `false` if ANY texture fails to load.
   */
  static bool load();
};
