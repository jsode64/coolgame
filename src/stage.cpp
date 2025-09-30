#include "stage.hpp"

#include "config.hpp"
#include "tile.hpp"

#include <cmath>
#include <numbers>

Stage::Stage() : tiles(), color(BLACK) {

}

Stage Stage::test() {
    Stage stage;

    // Give bodies.
    stage.tiles.push_back(Tile((Rectangle){ 200, 300, 400, 150 }));
    stage.tiles.push_back((Rectangle){ 100, 200, 100, 250 });
    stage.tiles.push_back((Rectangle){ 600, 250, 100, 100 });
    stage.tiles.push_back(Tile(300, 100, 200, 50, [](const Tile& tile){
        float x = 300.0f + (std::sin(GetTime() * std::numbers::pi / 4.0) * 300.0);
        return (Vector2){ x - tile.body.x, 0.0f };
    }));

    return stage;
}

// WIP
Stage Stage::stage_one(){
    /*Stage stage;
    stage.tiles.push_back(Tile(100, 100, 80, 20, [](const Tile& _){return (Vector2){0.0f, .20f}}))
    

    
    float center_x = WIN_W / 2;
    float center_y =  WIN_H / 2;
    stage.bodies.push_back((Rectangle){ center_x, center_y, 400, 100});

    Rectangle platform= {100, 100, 80, 20};
    Vector2 platform_vec = {0.0f, 2.0f};

    bool isPlatformPresent = true;
    const double toggleTime = 3.0;
    */
}

const std::vector<Tile>& Stage::get_bodies() const {
    return tiles;
}

void Stage::update() {
    for (auto& tile : tiles) {
        tile.update();
    }
}

void Stage::draw() const {
    for (const auto& tile : tiles) {
        DrawRectangleRec(tile.body, color);
    }
}
