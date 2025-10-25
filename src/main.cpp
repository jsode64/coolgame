/*
                THIS IS A TEST PROGRAM
                DO NOT MERGE INTO MAIN
                IT DOESN'T WORK


*/






#include <iostream>

#include <variant>

#include "raylib.h"

#include "config.hpp"
#include "game.hpp"


int32_t screenW;
int32_t screenH;

int main() {
  SetTraceLogLevel(LOG_NONE);
  InitWindow(WIN_W, WIN_H, "Cool Game");
  SetTargetFPS(60);

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
