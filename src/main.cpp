#include <iostream>

#include "raylib.h"

#include "config.hpp"
#include "game.hpp"



int main() {
    // Initialize window.
    InitWindow(WIN_W, WIN_H, "Cool Game");

    // Initialize Audio
    void InitAudioDevice();

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
