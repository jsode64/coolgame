#include "stage.hpp"

#include "util.hpp"
#include "tile.hpp"

#include <cmath>
#include <numbers>

Stage::Stage() : tiles(), color(BLUE) {}

Stage Stage::test() {
  Stage stage;

  stage.tiles.push_back(Tile(200.f, 400.f, 600.f, 50.f));
  stage.tiles.push_back(Tile(100.f, 300.f, 100.f, 150.f));
  stage.tiles.push_back(Tile(600.f, 300.f, 200.f, 50.f));
  stage.tiles.push_back(Tile(0.f, 300.f, 100.f, 50.f, 1.f));

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

std::vector<Tile> &Stage::get_tiles() { return tiles; }

void Stage::update() {
  for (auto &tile : tiles) {
    tile.update();
  }
}

void Stage::draw() const {
  for (const auto &tile : tiles) {
    auto scaled = rect_to_win(tile.body);
    DrawRectangleRec(scaled, color);
  }
}
