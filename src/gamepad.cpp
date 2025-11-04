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
        // Get axis values
        float leftStickX = GetGamepadAxisMovement(controller, GAMEPAD_AXIS_LEFT_X);
        float leftStickY = GetGamepadAxisMovement(controller, GAMEPAD_AXIS_LEFT_Y);
        float rightStickX = GetGamepadAxisMovement(controller, GAMEPAD_AXIS_RIGHT_X);
        float rightStickY = GetGamepadAxisMovement(controller, GAMEPAD_AXIS_RIGHT_Y);
        float leftTrigger = GetGamepadAxisMovement(controller, GAMEPAD_AXIS_LEFT_TRIGGER);
        float rightTrigger = GetGamepadAxisMovement(controller, GAMEPAD_AXIS_RIGHT_TRIGGER);

        // Calculate deadzones
        if (leftStickX > -leftStickDeadzoneX && leftStickX < leftStickDeadzoneX) leftStickX = 0.0f;
        if (leftStickY > -leftStickDeadzoneY && leftStickY < leftStickDeadzoneY) leftStickY = 0.0f;
        if (rightStickX > -rightStickDeadzoneX && rightStickX < rightStickDeadzoneX) rightStickX = 0.0f;
        if (rightStickY > -rightStickDeadzoneY && rightStickY < rightStickDeadzoneY) rightStickY = 0.0f;
        if (leftTrigger < leftTriggerDeadzone) leftTrigger = -1.0f;
        if (rightTrigger < rightTriggerDeadzone) rightTrigger = -1.0f;
    }
    else {
        id = "Controller not found!!";
    }
}

Gamepad Gamepad::giveController(Gamepad &gamepad) {
    return *this;
}

