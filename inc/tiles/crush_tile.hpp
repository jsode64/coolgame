#pragma once

#include "../tile.hpp"

class CrushTile: public Tile {
private:
    /** @brief The y coordinate to slam onto. */
    float ground;

public:
    CrushTile(float x, float y, float w, float h, float ground);

    void update() override;
};
