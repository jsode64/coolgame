#include "game.hpp"
#include "gamepad.hpp"

#include "raylib.h"

#include "fighters/stabby.hpp"
#include "fighters/oscar.hpp"
#include "fighters/slug.hpp"

Game::Game() : stage(Stage::test()), fighters(), attacks(), controllers(0,1,2,3) {
  fighters.emplace_back(std::make_unique<Stabby>(KEY_A, KEY_D, KEY_W, KEY_S, controllers[0]));
  fighters.emplace_back(
      std::make_unique<Oscar>(KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN, controllers[1]));
  fighters.emplace_back(std::make_unique<Slug>(KEY_J, KEY_L, KEY_I, KEY_K, controllers[2]));
}

void Game::update() {
  stage.update();
  controllers[0].update();
  for (auto &fighter : fighters)
    fighter->update(*this);
  for (auto &attack : attacks) {
    attack->update(*this);
    attack->handle_collision(fighters);
  }

  // Remove attacks that are done.
  attacks.erase(std::remove_if(attacks.begin(), attacks.end(),
                               [](const std::unique_ptr<Attack> &attack) {
                                 return attack->is_done();
                               }),
                attacks.end());
}

void Game::draw() const {
  stage.draw();
  controllers[0].id_display();
  for (const auto &fighter : fighters)
    fighter->draw();
  for (const auto &attack : attacks)
    attack->draw();
}

Stage &Game::get_stage() { return stage; }

std::vector<std::unique_ptr<Fighter>> &Game::get_fighters() { return fighters; }

std::list<std::unique_ptr<Attack>> &Game::get_attacks() { return attacks; }

void Game::push_attack(std::unique_ptr<Attack> attack) {
  attacks.push_back(std::move(attack));
}
