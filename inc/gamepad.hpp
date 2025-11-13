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

        // This creates a gamepad of a specified port number
        Gamepad(int portin);

        // This checks if a gamepad is available
        bool gamepad_check();

        // This displays the ID to the screen
        void id_display() const;

        // This updates the controller
        void update();

        // This chacks the controller ID
        void id_check();

        // This returns the Controller Object
        Gamepad giveController();

        // This returns the Controller Port Number
        int portReturn();
};