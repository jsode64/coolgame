#include "game.hpp"

#include "raylib.h"

#include "fighters/luie.hpp"
#include "fighters/oscar.hpp"

Game::Game()
    : stage(Stage::test()), fighters(), attacks() {
    fighters.push_back(std::make_unique<Luie>(KEY_A, KEY_D, KEY_W, KEY_S));
    fighters.push_back(std::make_unique<Oscar>(KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN));
}

void Game::update() {
    stage.update();

    for (auto& fighter: fighters) {
        fighter->update(stage, attacks);
    }

    for(auto& tile : stage.get_bodies()) {
        tile.touch_test();
    }

    for(auto& tile : stage.get_bodies()) {
        tile.rise_test();
    }


    // Update attacks and remove finished ones.
    for (size_t i = 0; i < attacks.size();) {
        bool finished = attacks[i].update(fighters);
        attacks[i].handle_collision(fighters);
        if (finished) {
            attacks.erase(attacks.begin() + i);
        } else {
            ++i;
        }
    }
}

void Game::draw() const {
    stage.draw();

    for (const auto& fighter: fighters) {
        fighter->draw();
    }

    for (const auto& attack : attacks) {
        attack.draw();
    }
}
