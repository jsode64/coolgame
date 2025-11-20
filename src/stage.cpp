#include "stage.hpp"

#include "tile.hpp"
#include "tiles/crush_tile.hpp"
#include "tiles/falling_tile.hpp"
#include "util.hpp"

#include <cmath>
#include <numbers>

Stage::Stage() : tiles(), color(BLUE) {}

Stage Stage::test() {
  Stage stage;

  stage.tiles.emplace_back(std::make_unique<Tile>(200.f, 400.f, 600.f, 50.f));
  stage.tiles.emplace_back(std::make_unique<Tile>(100.f, 300.f, 100.f, 150.f));
  stage.tiles.emplace_back(std::make_unique<Tile>(600.f, 300.f, 200.f, 50.f));
  stage.tiles.emplace_back(
      std::make_unique<FallingTile>(0.f, 300.f, 100.f, 50.f, 1.));

  return stage;
}

Stage Stage::stage_one() {
  Stage stage;

  stage.tiles.emplace_back(
      std::make_unique<FallingTile>(100.f, 340.f, 760.f, 200.f, 0.5f));
  stage.tiles.emplace_back(std::make_unique<Tile>(200.f, 400.f, 100.f, 140.f));
  stage.tiles.emplace_back(std::make_unique<Tile>(660.f, 400.f, 100.f, 140.f));
  stage.tiles.emplace_back(std::make_unique<Tile>(420.f, 500.f, 100.f, 40.f));

  return stage;
}

Stage Stage::stage_two() {
  Stage stage;

  stage.tiles.emplace_back(std::make_unique<Tile>(0.f, 500.f, 960.f, 40.f));
  stage.tiles.emplace_back(
      std::make_unique<CrushTile>(430.f, -100.f, 200.f, 600.f, 500.f));

  return stage;
}

std::vector<std::unique_ptr<Tile>> &Stage::get_tiles() { return tiles; }

void Stage::update() {
  for (auto &tile : tiles) {
    tile->update();
  }
}

void Stage::draw() const {
  for (const auto &tile : tiles) {
    auto scaled = rect_to_win(tile->get_body());
    DrawRectangleRec(scaled, color);
  }
}
