#include "stage.hpp"

Stage::Stage(float x, float y, float w, float h, Color color)
    :body({ x, y, w, h }), color(color) {

}

Rectangle Stage::get_body() const {
    return body;
}

void Stage::draw() const {
    DrawRectangleRec(body, color);
}
