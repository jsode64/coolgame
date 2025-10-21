#pragma once

#include <functional>

#include "raylib.h"

class Tile {
public:
  using UpdateFn = std::function<void(Tile &)>;

public:
  static constexpr float RISE_FALL_SPEED = 2.0f;
  inline static const UpdateFn NO_OP = [](Tile &_) {};

  Rectangle body;
  Vector2 v;

  UpdateFn updateFn;

  bool canFall;
  float stoodOnTime;
  float time;
  float home_y;

public:
  Tile(float x, float y, float w, float h, UpdateFn updateFn = NO_OP);

  Tile(float x, float y, float w, float h, float time);

  /**
   * Updates the tile's position then its velocity (using `Tile::updateFn`).
   */
  void update();

  void stood_on();

private:
  /**
   * Handles tile falling/rising.
   */
  void handle_rise_fall();
};

static const std::function<Vector2(const Tile &)> STATIONARY_TILE_FN =
    [](const Tile &_) { return (Vector2){0.0f, 0.0f}; };
