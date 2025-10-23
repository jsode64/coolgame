#pragma once

#include "raylib.h"
#include "tile.hpp"

#include <tuple>
#include <vector>

class Stage {
    private:

        /// @brief A collection of the stage's bodies.
        std::vector<Tile> tiles;

        /// @brief The stage's color.
        Color color;

        int stageWidth;
        int stageHeight;

    public:
        Stage();

        /// @return Returns the test stage.
        static Stage test();
        static Stage stage_one();

        /// @return If any body collides with one of the stage's, returns `true` and itself.
        const std::vector<Tile>& get_bodies() const;

        /// @brief Updates the stage's tiles.
        void update();

        /// @brief Draws the stage.
        void draw() const;

        /// @brief Returns Stage Blastzone Width
        int getStageWidth() const;

        /// @brief Returns Stage Blastzone Height
        int getStageHeight() const;
};
