#include <iostream>

#include "raylib.h"

#include "config.hpp"
#include "player.hpp"
#include "stage.hpp"
#include "attack.hpp"
#include "fighters/oscar.hpp"
#include "fighters/luie.hpp"

int main() {
    // Initialize window.
    InitWindow(WIN_W, WIN_H, "Cool Game");
    SetTargetFPS(60);

    //Image Loading
    Texture2D playerImg = LoadTexture("assets/placeholderman.png");

    //Player p(RED, KEY_A, KEY_D, KEY_SPACE, 0);
    Luie d(KEY_A, KEY_D, KEY_W);
    Oscar p(KEY_LEFT, KEY_RIGHT, KEY_UP);

    Attack jab(GREEN, BLUE, KEY_F);

    Stage stage = Stage::test();

    // Main game loop
    while (!WindowShouldClose()) {
        stage.update();
        p.update(stage);
        d.update(stage);
        //jab.update(p);

        // Render in here:
        BeginDrawing();
        ClearBackground(BLUE);
        DrawFPS(0, 0);
        
        p.draw();
        d.draw();
        stage.draw();

        EndDrawing();
    }

    //Unload Images
    UnloadTexture(playerImg);
    
    CloseWindow();
}
