#include "tile.hpp"

#include "raylib.h"

const static std::function<Vector2(const Tile&)> STATIONARY_FN =
    [](const Tile& _){ return(Vector2){ 0.0f, 0.0f }; };

Tile::Tile(Rectangle body)
    : body(body), v({ 0.0f, 0.0f }), updateFn(STATIONARY_FN) {

}

Tile::Tile(Rectangle body, std::function<Vector2(const Tile&)> updateFn)
    : body(body), v({ 0.0f, 0.0f }), updateFn(updateFn) {

}

Tile::Tile(float x, float y, float w, float h, std::function<Vector2(const Tile&)> updateFn)
    : body({ x, y, w, h }), v({ 0.0f, 0.0f }), updateFn(updateFn) {

}

void Tile::update() {
    // Update velocity.
    v = updateFn(*this);

    // Update position.
    body.x += v.x;
    body.y += v.y;
}
