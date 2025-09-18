#pragma once

#include "raylib.h"

class Stage {
    private:

        Rectangle body;
        Color color;

    public:
        Stage(float x, float y, float w, float h, Color color);

        /**
         * Returns the stage's body.
         */
        Rectangle get_body() const;

        /**
         * Draws the platform.
         */
        void draw() const;
};