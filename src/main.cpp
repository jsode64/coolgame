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
  }

  Game game;

  // Main game loop
  while (!WindowShouldClose()) {
    game.update();

    // Render in here:
    BeginDrawing();
    ClearBackground(BLUE);
    DrawFPS(0, 0);

    game.draw();

    EndDrawing();
  }

  CloseAudioDevice();

  CloseWindow();
}
