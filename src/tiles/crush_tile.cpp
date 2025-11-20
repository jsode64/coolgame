#include "tiles/crush_tile.hpp"

#include <iostream>

#include "config.hpp"

CrushTile::CrushTile(float x, float y, float w, float h, float ground)
    : Tile(x, y, w, h), ground(ground) {}

void CrushTile::update() {
  if (body.y >= ground - body.height) {
    v.y = -3.f;
  } else if (body.y < -body.height) {
    v.y = 15.f;
  }

  Tile::update();
}
