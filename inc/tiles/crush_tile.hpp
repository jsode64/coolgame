#pragma once

#include "../tile.hpp"

class CrushTile: public Tile {
private:
    /** @brief The speed to slide at. */
    float speed;

public:
    CrushTile(float x, float y, float w, float h, float speed);

    void update() override;
};
