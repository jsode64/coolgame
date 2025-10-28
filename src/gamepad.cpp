#include "gamepad.hpp"

#include "raylib.h"

Gamepad::Gamepad() {

}

bool Gamepad::gamepad_check() {
    bool controller_detect = IsGamepadAvailable(controller);
    return controller_detect;
}

void Gamepad::id_check(){
    id = GetGamepadName(controller); 
}

void Gamepad::id_display() const{
    DrawText(id, 190, 200, 20, RED);
}

void Gamepad::update() {
    if (gamepad_check()) {
        id_check();
    }
    else {
        id = "Controller not found!!";
    }
}

