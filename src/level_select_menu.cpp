#include "level_select_menu.hpp"

#include "util.hpp"

LevelSelectMenu::LevelSelectMenu()
    : options{"Level 1", "Level 2", "Level 3", "Level 4", "Level 5"}, choice(0),
      selected(false) {}

bool LevelSelectMenu::choice_made() const { return selected; }

size_t LevelSelectMenu::get_choice() const { return choice; }

void LevelSelectMenu::update() {
  if (IsKeyPressed(KEY_DOWN)) {
    choice = (choice + 1) % options.size();
  }
  if (IsKeyPressed(KEY_UP)) {
    choice = choice == 0 ? options.size() - 1 : choice - 1;
  }

  if (IsKeyPressed(KEY_ENTER)) {
    selected = true;
  }
}

void LevelSelectMenu::draw() const {
  for (size_t i = 0; i < options.size(); i++) {
    Rectangle body =
        rect_to_win(Rectangle(50.f, 50.f + (float(i) * 75.f), 860.f, 50.f));
    DrawRectangleRec(body, i == choice ? GREEN : RED);
    DrawText(options[i], body.x, body.y, 12, BLACK);
  }
}
