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

void Gamepad::update() {

}