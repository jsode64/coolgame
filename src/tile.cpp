#include "tile.hpp"
#include "config.hpp"
#include "raylib.h"

Tile::Tile(float x, float y, float w, float h)
    : body(x, y, w, h), v(0.f, 0.f) {}

Rectangle Tile::get_body() const { return body; }

Vector2 Tile::get_v() const { return v; }

void Tile::update() {
  body.x += v.x;
  body.y += v.y;
}

void Tile::stood_on() {}
