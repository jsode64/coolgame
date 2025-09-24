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
    Player dummy(WHITE, 0, 0, 0, 0);

    Stage stage = Stage::new_random();

    // Main game loop
    while (!WindowShouldClose()) {
        p.update(stage);
        dummy.update(stage);

        // Render in here:
        BeginDrawing();
        ClearBackground(BLUE);
        DrawFPS(0, 0);
        
        p.draw();
        dummy.draw();
        stage.draw();

        EndDrawing();
    }

    CloseWindow();
}
