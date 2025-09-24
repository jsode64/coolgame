#pragma once

#include "raylib.h"

/**
 * Loosely checks for collision with two rectangles (uses `<`, not `<=`).
 * 
 * @return True if the rectangles collide, false if not.
 */
bool recs_collide(Rectangle a, Rectangle b);
