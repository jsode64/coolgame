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
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(WIN_W, WIN_H, "Cool Game");
  SetTargetFPS(60);

  Game game;

  // Main game loop
  while (!WindowShouldClose()) {
    if (IsWindowResized() && !IsWindowFullscreen())
        {
            screenW = GetScreenWidth();
            screenH = GetScreenHeight();
        }

        // check for alt + enter
 		if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
 		{
            // see what display we are on right now
 			int display = GetCurrentMonitor();
 
            
            if (IsWindowFullscreen())
            {
                // if we are full screen, then go back to the windowed size
                SetWindowSize(screenW, screenH);
            }
            else
            {
                // if we are not full screen, set the window size to match the monitor we are on
                SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
            }
 
            // toggle the state
 			ToggleFullscreen();
 		}


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
