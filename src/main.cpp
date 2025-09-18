#include <iostream>

#include "raylib.h"

#include "config.hpp"
#include "player.hpp"
#include "stage.hpp"

int main() {
    // Initialize window.
    InitWindow(WIN_W, WIN_H, "Cool Game");
    SetTargetFPS(60);


    Player p(RED, KEY_A, KEY_D, KEY_SPACE, 0);

    Stage stage(200, 300, 400, 150, BROWN);


    while (!WindowShouldClose()) {
        p.update(stage);

        // Render in here:
        BeginDrawing();
        ClearBackground(BLUE);
        DrawFPS(0, 0);
        
        p.draw();
        stage.draw();

        EndDrawing();
    }

    CloseWindow();
}
