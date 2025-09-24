#pragma once

#include "raylib.h"

#include <tuple>
#include <vector>

class Stage {
    private:

        /// @brief A collection of the stage's bodies.
        std::vector<Rectangle> bodies;

        /// @brief The stage's color.
        Color color;

    public:
        Stage();

        /// @return A new random stage.
        static Stage new_random();

        /// @return If any body collides with one of the stage's, returns `true` and itself.
        const std::vector<Rectangle>& get_bodies() const;

        /// @brief Draws the stage.
        void draw() const;

        Stage stage_one();
};