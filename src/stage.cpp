#include "stage.hpp"

#include "assets.hpp"
#include "tile.hpp"
#include "tiles/crush_tile.hpp"
#include "tiles/falling_tile.hpp"
#include "util.hpp"

#include <cmath>
#include <numbers>

Stage::Stage(Texture2D bg, Color color) : tiles(), bg(bg), color(color) {}

Stage Stage::stage_one() {
  Stage stage(Assets::SKY_BG, PURPLE);

  stage.tiles.emplace_back(std::make_unique<Tile>(150.f, 450.f, 660.f, 50.f));

  return stage;
}

Stage Stage::stage_two() {
  Stage stage(Assets::FOREST_BG, BROWN);

  stage.tiles.emplace_back(
      std::make_unique<FallingTile>(100.f, 340.f, 760.f, 200.f, 0.5f));
  stage.tiles.emplace_back(std::make_unique<Tile>(200.f, 400.f, 100.f, 140.f));
  stage.tiles.emplace_back(std::make_unique<Tile>(660.f, 400.f, 100.f, 140.f));
  stage.tiles.emplace_back(std::make_unique<Tile>(420.f, 500.f, 100.f, 40.f));

  stage.bg = Assets::CITY_BG;

  return stage;
}

Stage Stage::stage_three() {
  Stage stage(Assets::CITY_BG, Color(75, 65, 65, 255));

  stage.tiles.emplace_back(std::make_unique<Tile>(0.f, 500.f, 960.f, 40.f));
  stage.tiles.emplace_back(
      std::make_unique<CrushTile>(0.f, 450.f, 75.f, 50.f, 1.5f));

  return stage;
}

Stage Stage::stage_four() {
  Stage stage(Assets::HELL_BG, YELLOW);

  stage.tiles.emplace_back(std::make_unique<Tile>(200.f, 450.f, 350.f, 1000.f));
  stage.tiles.emplace_back(std::make_unique<Tile>(400.f, 400.f, 200.f, 1000.f));
  stage.tiles.emplace_back(std::make_unique<Tile>( 650.f, 500.f, 75.f, 1000.f));

  return stage;
}

Stage Stage::stage_five() {
  Stage stage(Assets::SKY_BG, BLUE);

  stage.tiles.emplace_back(std::make_unique<Tile>(465.f, 500.f, 30.f, 25.f));
  stage.tiles.emplace_back(std::make_unique<Tile>(100.f, 150.f, 120.f, 25.f));
  stage.tiles.emplace_back(std::make_unique<Tile>(740.f, 200.f, 120.f, 25.f));
  stage.tiles.emplace_back(std::make_unique<Tile>(300.f, 350.f, 100.f, 25.f));
  stage.tiles.emplace_back(std::make_unique<Tile>(560.f, 300.f, 100.f, 25.f));

  return stage;
}

std::vector<std::unique_ptr<Tile>> &Stage::get_tiles() { return tiles; }

void Stage::update() {
  for (auto &tile : tiles) {
    tile->update();
  }
}

void Stage::draw() const {
  auto src = Rectangle(0.f, 0.f, 400.f, 224.f);
  auto dst = Rectangle(0.f, 0.f, GetScreenWidth(), GetScreenHeight());
  DrawTexturePro(bg, src, dst, Vector2(0.f, 0.f), 0.f, WHITE);

  for (const auto &tile : tiles) {
    auto scaled = rect_to_win(tile->get_body());
    DrawRectangleRec(scaled, color);
  }
}
