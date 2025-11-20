#include <iostream>

#include "raylib.h"

#include "assets.hpp"
#include "config.hpp"
#include "game.hpp"

int main() {
  SetTraceLogLevel(LOG_NONE);
  InitWindow(SIM_W, SIM_H, "Cool Game");
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  SetTargetFPS(60);

  if (!Assets::load()) {
    std::printf("Failed to load assets!\n");
    return 1;
  }

  Game game;
  auto sb = LoadTexture("assets/hi.jpg");

  while (!WindowShouldClose()) {
    // Render in here:
    BeginDrawing();
    ClearBackground(WHITE);
    DrawTexturePro(Assets::FOREST_BG, Rectangle(0.f, 0.f, 800.f, 448.f),
                   Rectangle(0.f, 0.f, GetScreenWidth(), GetScreenHeight()),
                   Vector2(0.f, 0.f), 0.f, WHITE);
    game.update();
    EndDrawing();
  }

  CloseAudioDevice();
  CloseWindow();
}
