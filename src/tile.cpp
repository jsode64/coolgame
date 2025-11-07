#include "tile.hpp"
#include "config.hpp"
#include "raylib.h"

Tile::Tile(float x, float y, float w, float h, UpdateFn updateFn)
    : body(x, y, w, h), v(0.0f, 0.0f), updateFn(updateFn), canFall(false),
      stoodOnTime(-1.0f), time(0.0f), home_y(y) {}

Tile::Tile(float x, float y, float w, float h, float time)
    : body(x, y, w, h), v(0.0f, 0.0f), updateFn(NO_OP), canFall(true),
      stoodOnTime(-1.0f), time(time), home_y(y) {}

void Tile::update() {
  // Update tile.
  updateFn(*this);

  if (canFall) {
    // If fallen below the screen, start moving up.
    if (body.y > SIM_H) {
      v.y = -RISE_FALL_SPEED;
    } else if (stoodOnTime > 0.0f && float(GetTime()) - stoodOnTime > time &&
               v.y >= 0.0f) {
      v.y = RISE_FALL_SPEED;
    }

    // Don't let rise beyond home.
    if (body.y < home_y) {
      body.y = home_y;
      v.y = 0.0f;
      stoodOnTime = -1.0f;
    }
  }

  // Update position.
  body.x += v.x;
  body.y += v.y;
}

void Tile::stood_on() {
  if (canFall && stoodOnTime < 0.0f) {
    stoodOnTime = float(GetTime());
  }
}

void Tile::handle_rise_fall() {
  // Only continue if the tile has falling active.
  if (!canFall) {
    return;
  }

  // Begin rising when reaching the bottom of the screen.
  if (body.y > SIM_H) {
    v.y = -RISE_FALL_SPEED;
    stoodOnTime = -1.0f;
  }

  // Fall if enough time has passed since stepped on.
  if (stoodOnTime > 0.0f && float(GetTime()) - stoodOnTime > time) {
    v.y = RISE_FALL_SPEED;
  }

  // Don't let rise beyond home.
  if (body.y < home_y) {
    body.y = home_y;
    v.y = 0.0f;
  }
}
