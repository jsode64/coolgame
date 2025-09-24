#include "util.hpp"

bool recs_collide(Rectangle a, Rectangle b) {
    return a.x < b.x + b.width
        && a.x + a.width > b.x
        && a.y < b.y + b.height
        && a.y + a.height > b.y;
}
