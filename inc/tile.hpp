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

        Tile(float x, float y, float w, float h, bool mov_tile, std::function<Vector2(const Tile&)> updateFn);
       
        /**
         * Updates the tile's position then its velocity (using `Tile::updateFn`).
         */
        void update();

        void drop();

        void touch_test() const;

        void timer() const;

        bool vert_timer(double time_set) const;

        void rise_test() const;

        void go_up();
};

static const std::function<Vector2(const Tile&)> STATIONARY_TILE_FN =
    [](const Tile& _){ return(Vector2){ 0.0f, 0.0f }; };
