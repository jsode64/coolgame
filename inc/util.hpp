#pragma once

#include "raylib.h"

/**
 * Returns the rectangle scaled from the simulation size to the window size.
 * 
 * @param rect The rectangle to be scaled
 * 
 * @return The scaled rectangle
 */
Rectangle rect_to_win(Rectangle rect);
