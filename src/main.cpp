#include <iostream>

#include "raylib.h"

#include "config.hpp"
#include "player.hpp"
#include "stage.hpp"
#include "attack.hpp"

int main() {
    // Initialize window.
    InitWindow(WIN_W, WIN_H, "Cool Game");
    SetTargetFPS(60);

    //Image Loading
    Texture2D playerImg = LoadTexture("assets/placeholderman.png");

    Player p(RED, KEY_A, KEY_D, KEY_SPACE, 0);
    Player dummy(WHITE, 0, 0, 0, 0);

    Attack jab(GREEN, BLUE, KEY_F);

    Stage stage = Stage::test();

    // Main game loop
    while (!WindowShouldClose()) {
        stage.update();
        p.update(stage);
        dummy.update(stage);
        jab.update(p);

        // Render in here:
        BeginDrawing();
        ClearBackground(BLUE);
        DrawFPS(0, 0);
        
        p.draw();
        dummy.draw();
        stage.draw();

        EndDrawing();
    }

    //Unload Images
    UnloadTexture(playerImg);
    
    CloseWindow();
}
