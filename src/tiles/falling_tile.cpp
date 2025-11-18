#include "tiles/falling_tile.hpp"

#include <iostream>

#include "config.hpp"

FallingTile::FallingTile(float x, float y, float w, float h, float time)
    : Tile(x, y, w, h), initY(y), time(time), stoodTime(-1.) {

}

void FallingTile::update() {
    if (body.y >= SIM_H + body.height) {
        // Rise after falling offscreen.
        v.y = -2.f * GRAVITY;
    } else if (v.y == 0.f && stoodTime > 0. && GetTime() - stoodTime >= time) {
        // Fall after stood on.
        v.y = 0.99f * GRAVITY;
        stoodTime = -1.;
    }

    // Stop rising at top.
    if (body.y < initY) {
        body.y = initY;
        v.y = 0.f;
        stoodTime = -1.;
    }

    Tile::update();
}

void FallingTile::stood_on() {
    if (stoodTime < 0.) {
        stoodTime = GetTime();
    }
}
