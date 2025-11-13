#pragma once

#include "raylib.h"
#include <string>

// NOTE: Gamepad name ID depends on drivers and OS
class Gamepad {

    private:
        int port;
        const char* id;

        const float leftStickDeadzoneX = 0.1f;
        const float leftStickDeadzoneY = 0.1f;
        const float rightStickDeadzoneX = 0.1f;
        const float rightStickDeadzoneY = 0.1f;
        const float leftTriggerDeadzone = -0.9f;
        const float rightTriggerDeadzone = -0.9f;
    public:

        Gamepad(int portin);

        bool gamepad_check();

        void id_display() const;

        void update();

        void id_check();

        Gamepad giveController();

        int portReturn();
};