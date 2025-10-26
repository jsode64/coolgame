#include "stage.hpp"

#include "config.hpp"
#include "tile.hpp"

#include <cmath>
#include <numbers>

Stage::Stage() : tiles(), color(BLACK), stageWidth(WIN_W), stageHeight(WIN_H) {}

Stage Stage::test() {
  Stage stage;

  

  // Give bodies.
  stage.tiles.push_back(Tile(200, 400, 600, 50));
  stage.tiles.push_back(Tile(100, 300, 100, 150));
  stage.tiles.push_back(Tile(600, 300, 200, 50));
  stage.tiles.push_back(Tile(300, 100, 200, 50, [](Tile &tile) {
    float x = 300.0f + (std::sin(GetTime() * std::numbers::pi * 2.0) * 300.0);
    tile.v.x = x - tile.body.x;
  }));
  stage.tiles.push_back(Tile(600, 350, 50, 50, [](Tile &tile) {
    float x = 450.0f + (std::sin(GetTime() * std::numbers::pi * 2.0) * 100.0);
    tile.v.x = x - tile.body.x;
  }));
  stage.tiles.push_back(Tile(0, 300, 100, 50, 1.0f));

  return stage;
}

// WIP
Stage Stage::stage_one() {
  Stage stage;

  stage.tiles.push_back(Tile(90, 300, 400, 50));

  stage.tiles.push_back(Tile(500, 300, 100, 50, 1.0f));

  stage.tiles.push_back(Tile(0, 300, 100, 50, 1.0f));

  return stage;
}

std::vector<Tile> &Stage::get_bodies() { return tiles; }

void Stage::update() {
  for (auto &tile : tiles) {
    tile.update();
  }
}

void Stage::draw() const {
  for (const auto &tile : tiles) {
    DrawRectangleRec(tile.body, color);
  }
}

int Stage::getStageHeight() const {
    return stageHeight;
}

int Stage::getStageWidth() const {
    return stageWidth;
}