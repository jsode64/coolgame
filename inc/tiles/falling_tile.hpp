#pragma once

#include "../tile.hpp"

class FallingTile: public Tile {
private:
    /** @brief The tile's initial/max y position. */
    float initY;

    /** @brief The time in seconds the tile will wait before falling after stood on. */
    double time;

    /** @brief The time in seconds since the tile has been stood on. */
    double stoodTime;

public:
    FallingTile(float x, float y, float w, float h, float time);

    void update() override;

    void stood_on() override;
};
