#include "game.hpp"

#include "raylib.h"

#include "fighters/oscar.hpp"
#include "fighters/slug.hpp"
#include "fighters/stabby.hpp"

Game::Game() : state(State::Open), stage({0}, WHITE), fighters(), attacks(), main_menu(), level_select_menu() {

}

void Game::update() {
  switch (state)
  {
  case State::Open:
    main_menu.update();
    main_menu.draw();
    if (main_menu.was_passed())
      state = State::LevelSelect;
    break;

  case State::LevelSelect:
    level_select_menu.update();
    level_select_menu.draw();
    if (level_select_menu.choice_made())
      init_play(level_select_menu.get_choice());
    break;

  case State::Play:
    update_play();
    draw();
    break;
  }
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

void Game::update_play() {
  // Press 'P' to return to main menu.
  if (IsKeyPressed(KEY_P) || fighters.size() <= 1) {
    main_menu = MainMenu();
    level_select_menu = LevelSelectMenu();
    state = State::Open;
    return;
  }

  stage.update();
  for (auto &fighter : fighters)
    fighter->update(*this);
  for (auto &attack : attacks) {
    attack->update(*this);
    attack->handle_collision(fighters);
  }

  // Remove fighters that are dead.
  fighters.erase(std::remove_if(fighters.begin(), fighters.end(),
                               [](const std::unique_ptr<Fighter> &fighters) {
                                 return!fighters->is_alive();
                               }),
                fighters.end());

  // Remove attacks that are done.
  attacks.erase(std::remove_if(attacks.begin(), attacks.end(),
                               [](const std::unique_ptr<Attack> &attack) {
                                 return attack->is_done();
                               }),
                attacks.end());
}

void Game::init_play(size_t i) {
  if (i == 0) {
    stage = Stage::stage_one();
  } else if (i == 1) {
    stage = Stage::stage_two();
  } else if (i == 2) {
    stage = Stage::stage_three();
  } else if (i == 3) {
    stage = Stage::stage_four();
  } else if (i == 4) {
    stage = Stage::stage_five();
   }
    else {
    throw std::runtime_error("Bad level select");
  }

  fighters.clear();
  attacks.clear();
  state = State::Play;

  fighters.emplace_back(std::make_unique<Stabby>(KEY_A, KEY_D, KEY_W, KEY_S));
  fighters.emplace_back(
      std::make_unique<Oscar>(KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN));
  fighters.emplace_back(std::make_unique<Slug>(KEY_J, KEY_L, KEY_I, KEY_K));
}
