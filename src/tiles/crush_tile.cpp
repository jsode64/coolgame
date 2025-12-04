#include "tiles/crush_tile.hpp"

#include <cmath>
#include <numbers>

#include "config.hpp"

CrushTile::CrushTile(float x, float y, float w, float h, float speed)
    : Tile(x, y, w, h), speed(speed) {}

void CrushTile::update() {
  float t = (1.f + std::sin(speed * float(GetTime()))) / 2.f;
  float targetX = (SIM_W - body.width) * t;
  v.x = targetX - body.x;

  Tile::update();
}
