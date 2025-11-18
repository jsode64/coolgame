#include "game.hpp"

#include "raylib.h"

#include "fighters/stabby.hpp"
#include "fighters/oscar.hpp"
#include "fighters/slug.hpp"

Game::Game() : currentState(State::Opening) {
  init(1);
}

void Game::handle_state(LevelMenu& level, OpeningMenu& opening, PauseMenu& paused) {
  switch(currentState) {
    case State::Opening:
      opening.draw(currentState);
      break;
    case State::Playing:
      update();
      draw();
      break;
    case State::Pause:
      paused.draw(currentState);
      break;
    case State::LevelSelect:
      level.draw(currentState);
      if (level.choice != 0) {
        init(level.choice);
        currentState = State::Playing;
        level.choice = 0;
      }
      break;
    case State::GameOver:
      break;
  }
}

void Game::update() {
  stage.update();
  for (auto &fighter : fighters)
    fighter->update(*this);
  for (auto &attack : attacks) {
    attack->update(*this);
    attack->handle_collision(fighters);
  }

  // Remove attacks that are done.
  attacks.erase(
    std::remove_if(
      attacks.begin(),
      attacks.end(),
      [](const std::unique_ptr<Attack> &attack) {
        return attack->is_done();
      }
    ),
    attacks.end()
  );
}

void Game::init(size_t i) {
  if (i == 2) {
    stage = Stage::test();
  } else {
    stage = Stage::stage_one();
  }

  fighters.clear();
  attacks.clear();

  fighters.emplace_back(std::make_unique<Stabby>(KEY_A, KEY_D, KEY_W, KEY_S));
  fighters.emplace_back(
      std::make_unique<Oscar>(KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN));
  fighters.emplace_back(std::make_unique<Slug>(KEY_J, KEY_L, KEY_I, KEY_K));
}

void Game::draw() const {
  stage.draw();
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
