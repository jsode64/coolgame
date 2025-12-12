#pragma once

#include <string>

#include "raylib.h"

class Button {
private:
  Rectangle body;
  std::string text;

public:
  Button(float x, float y, float w, float h, const std::string &text);

  /** @brief Draws the button with the given color. */
};
