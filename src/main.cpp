#include <iostream>

#include "raylib.h"

#include "assets.hpp"
#include "config.hpp"
#include "game.hpp"

int main() {
  SetTraceLogLevel(LOG_NONE);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(WIN_W, WIN_H, "Cool Game");
  SetTargetFPS(60);

  if (!Assets::load()) {
    std::printf("Failed to load assets!\n");
    return 1;
  }

  Game game;
  auto sb = LoadTexture("assets/hi.jpg");

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
