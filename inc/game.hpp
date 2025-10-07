#pragma once

#include <vector>
#include <memory>

#include "attack.hpp"
#include "fighter.hpp"
#include "stage.hpp"

class Game {
    private:

        Stage stage;

    std::vector<std::unique_ptr<Fighter>> fighters;
        std::vector<Attack> attacks;

    public:

        Game();

        void update();

        void draw() const;
};
