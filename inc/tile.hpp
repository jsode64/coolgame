#pragma once

#include <functional>

#include "raylib.h"

class Tile {
    public:

        Rectangle body;
        Vector2 v;
        std::function<Vector2(const Tile&)> updateFn;
        mutable bool touch;
        bool mov_tile;
        mutable double time;
        mutable bool fall;
        float init_y;
        mutable bool rise;
    
    public: 

        Tile(Rectangle body);

        Tile(Rectangle body, std::function<Vector2(const Tile&)> updateFn);

        Tile(float x, float y, float w, float h, std::function<Vector2(const Tile&)> updateFn);

        Tile(float x, float y, float w, float h, bool touch, bool mov_tile, bool fall, double time, std::function<Vector2(const Tile&)> updateFn);
        /**
         * Updates the tile's position then its velocity (using `Tile::updateFn`).
         */
        void update();
        void drop();
        const void touch_test() const;
        const void timer() const;
        const bool vert_timer(double time_set) const;
        const void rise_test() const;
        void go_up();
};
