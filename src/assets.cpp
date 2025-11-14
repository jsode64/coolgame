#include "assets.hpp"

#include <iostream>

Texture2D Assets::FOREST_BG = {0};

Texture2D Assets::OSCAR_IDLE = {0};
Texture2D Assets::OSCAR_WALK = {0};

Texture2D Assets::STABBY_IDLE = {0};
Texture2D Assets::STABBY_WALK = {0};
Texture2D Assets::STABBY_SWING = {0};
Texture2D Assets::STABBY_JUMP = {0};
Texture2D Assets::STABBY_AIR_ATTACK = {0};

Texture2D Assets::SLUG_IDLE = {0};

/**
 * Loads the given file into the texture and returns `true` on success or
 * `false` on error.
 */
bool load_asset(Texture2D &tex, const char *path) {
  tex = LoadTexture(path);
  return tex.id != 0;
}

bool Assets::load() {
  return load_asset(FOREST_BG, "assets/bgs/forest_bg.png") &&
         load_asset(OSCAR_IDLE, "assets/foo.png") &&
         load_asset(OSCAR_WALK, "assets/mansheet.png") &&
         load_asset(STABBY_IDLE, "assets/stabby/stabby_idle.png") &&
         load_asset(STABBY_WALK, "assets/stabby/stabby_walk.png") &&
         load_asset(STABBY_SWING, "assets/stabby/stabby_swing.png") &&
         load_asset(STABBY_JUMP, "assets/stabby/stabby_jump.png") &&
         load_asset(STABBY_AIR_ATTACK, "assets/stabby/stabby_air_attack.png") &&
         load_asset(SLUG_IDLE, "assets/slug/slug.png");
}
