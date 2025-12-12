#include "util.hpp"

#include "config.hpp"

Rectangle rect_to_win(Rectangle rect) {
  float x = float(GetScreenWidth()) / float(SIM_W);
  float y = float(GetScreenHeight()) / float(SIM_H);

  return Rectangle(rect.x * x, rect.y * y, rect.width * x, rect.height * y);
}
