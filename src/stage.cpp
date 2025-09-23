#include "stage.hpp"

#include <random>

Stage::Stage() : bodies(), color(BLACK) {

}

Stage Stage::new_random() {
    Stage stage;

    // Give bodies.
    stage.bodies.push_back((Rectangle){ 200, 300, 400, 150 });
    stage.bodies.push_back((Rectangle){ 100, 200, 100, 250 });

    return stage;
}

std::tuple<bool, Rectangle> Stage::get_collision(Rectangle a) const {
    for (const auto& b : bodies) {
        if (CheckCollisionRecs(a, b)) {
            return std::make_tuple(true, b);
        }
    }

    return std::make_tuple(false, (Rectangle){ 0 });
}

void Stage::draw() const {
    for (const auto& body : bodies) {
        DrawRectangleRec(body, color);
    }
}
