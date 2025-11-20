#include "main_menu.hpp"

#include "raylib.h"

#include "util.hpp"

MainMenu::MainMenu() : selected(false) {

}

bool MainMenu::was_passed() const {
    return selected;
}

void MainMenu::update() {
    selected = selected || IsKeyDown(KEY_ENTER);
}

void MainMenu::draw() const {
    Rectangle body = rect_to_win(Rectangle(0.f, 0.f, 960.f, 540.f));
    DrawRectangleRec(body, Color(200, 150, 25));

    DrawText("Welcome to Fight Night!", 100, 100, 50, RED);
}
