#include "stage.hpp"
#include "config.hpp"

#include <random>

Stage::Stage() : bodies(), color(BLACK) {

}

Stage Stage::new_random() {
    Stage stage;

    // Give bodies.
    stage.bodies.push_back((Rectangle){ 200, 300, 400, 150 });
    stage.bodies.push_back((Rectangle){ 100, 200, 100, 250 });
    stage.bodies.push_back((Rectangle){ 600, 250, 100, 100 });

    return stage;
}

// WIP
Stage Stage::stage_one(){
    Stage stage;
    
    float center_x = WIN_W / 2;
    float center_y =  WIN_H / 2;
    stage.bodies.push_back((Rectangle){ center_x, center_y, 400, 100});

    Rectangle platform= {100, 100, 80, 20};
    Vector2 platform_vec = {0.0f, 2.0f};

    bool isPlatformPresent = true;
    const double toggleTime = 3.0;

}

const std::vector<Rectangle>& Stage::get_bodies() const {
    return bodies;
}

void Stage::draw() const {
    for (const auto& body : bodies) {
        DrawRectangleRec(body, color);
    }
}
