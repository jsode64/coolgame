#include "tile.hpp"
#include "config.hpp"
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

Tile::Tile(float x, float y, float w, float h, bool touch, bool mov_tile, bool fall, double time, std::function<Vector2(const Tile&)> updateFn) 
    : body({x, y, w, h}), v({0.0f, 0.0f}), touch(touch), mov_tile(mov_tile), fall(fall), rise(fall), time(0.0), init_y(y), updateFn(updateFn) {

}

// Lowers the tile out of bounds after it was touched.
void Tile::drop(){
    if(fall == true && body.y < WIN_H + 100){
        v.y = 10.0f;
        body.y += v.y;
    }
}

// Raises tile back to original position after it was lowered.
void Tile::go_up(){
    if(rise == true && body.y > init_y)
    {
        v.y = 10.0f;
        body.y -= v.y;
    }
}

//creates timer for raising/dropping tiles.
const void Tile::timer() const {

    time = GetTime();

}

//tests to see if go_up() should be called.
const void Tile::rise_test() const{
    if(fall == true && body.y >= WIN_H + 100)
    {
        timer();
       if(vert_timer(time)){
        fall = false;
        rise = true;
       }
    }
}

//checks to see if specified time has elapsed after tile was touched.
const bool Tile::vert_timer(double time_set) const{
    double elapsed = GetTime();
    if ((elapsed - time_set) > 5.0)
    {
        return true;
    }
    else{
        return false;
    }
}

//Checks to see if tile was touched by players.
const void Tile::touch_test() const{
    if(mov_tile == true && touch == true && time == 0.0){
        timer();
    }

    else if(mov_tile == true && touch == true && time != 0.0){
        if(vert_timer(time)) {
            fall = true;
            touch = false;
        }
    }
}

void Tile::update() {
    // Update velocity.
    v = updateFn(*this);

    // Update position.
    body.x += v.x;
    body.y += v.y;
    drop();
    go_up();
}
