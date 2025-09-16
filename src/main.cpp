#include <iostream>

#include "raylib.h"

int main() {
    InitWindow(800, 450, "Cool Game");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Raylib works!", 0, 0, 20, BLACK);
        EndDrawing();
    }
    CloseWindow();
}
