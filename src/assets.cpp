#include "assets.hpp"

#include <iostream>

Texture2D Assets::FOO = {0};

/**
 * Loads the given file into the texture and returns `true` on success or
 * `false` on error.
 */
bool load_asset(Texture2D &tex, const char *path) {
  tex = LoadTexture(path);
  return tex.id != 0;
}

bool Assets::load() {
  bool success = load_asset(FOO, "assets/foo.png");

  return success;
}
