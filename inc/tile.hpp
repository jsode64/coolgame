#pragma once

#include <functional>

#include "raylib.h"

class Tile {
    public:

        Rectangle body;
        Vector2 v;
        std::function<Vector2(const Tile&)> updateFn;
    
    public: 

        Tile(Rectangle body);

        Tile(Rectangle body, std::function<Vector2(const Tile&)> updateFn);

        Tile(float x, float y, float w, float h, std::function<Vector2(const Tile&)> updateFn);

        /**
         * Updates the tile's position then its velocity (using `Tile::updateFn`).
         */
        void update();
};
