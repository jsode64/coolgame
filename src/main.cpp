#include <iostream>

#include "raylib.h"

#include "assets.hpp"
#include "config.hpp"
#include "game.hpp"

int main() {
  SetTraceLogLevel(LOG_NONE);
  InitWindow(WIN_W, WIN_H, "Cool Game");
  SetTargetFPS(60);

  if (!Assets::load()) {
    std::printf("Failed to load assets!\n");
    return 1;
  }

  Game game;
  auto sb = LoadTexture("assets/hi.jpg");

  while (!WindowShouldClose()) {
    game.update();

    // Render in here:
    BeginDrawing();
    ClearBackground(WHITE);
    DrawTexturePro(Assets::FOREST_BG, Rectangle(0.f, 0.f, 800.f, 448.f),
                   Rectangle(0.f, 0.f, WIN_W, WIN_H), Vector2(0.f, 0.f), 0.f,
                   WHITE);
    game.draw();
    EndDrawing();
  }

  CloseAudioDevice();
  CloseWindow();
}
