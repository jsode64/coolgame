#include "openingmenu.hpp"

Rectangle ls = {160.0f, 110.0f, 130.0f, 20.0f};
Rectangle sb = {160.0f, 150.0f, 85.0f, 20.0f};

Buttons levelSelect = Buttons(ls, RED, GREEN, "Level Select", 1);
Buttons settings = Buttons(sb, RED, GREEN, "Settings", 2);

OpeningMenu::OpeningMenu(int spos, int mpos, int32_t upKey, int32_t downKey, int32_t select) 
	: spos(spos), mpos(mpos), upkey(upKey), downkey(downKey), select(select) {
	opening_options.push_back(levelSelect);
	opening_options.push_back(settings);
}

void OpeningMenu::drawButtons(std::vector<Buttons>& buttons) {
	for (auto& button : buttons) {
		Color currentColor = (spos == button.button_pos) ? button.selectColor : button.color;
		DrawRectangleRec(button.bounds, currentColor);
		DrawText(button.text.c_str(), button.bounds.x, button.bounds.y, 20, BLACK);
	}
}

void OpeningMenu::draw(State& state) {
	// To be replaced with texture/image
	DrawRectangle(0, 0, 800, 450, WHITE);
	DrawText("WELCOME TO FIGHT NIGHT!", 50, 50, 20, BLACK);
	drawButtons(opening_options);
	navigate(state);
}

void OpeningMenu::navigate(State& state) {
	bool down = IsKeyPressed(downkey);
	bool up = IsKeyPressed(upkey);
	bool sel = IsKeyPressed(select);

	if(down){
		if(spos >= mpos) {
			spos = 1;
		}

		else {
			spos ++;
		}
	}

	if(up) {
		if(spos == 1) {
			spos = 2;
		}

		else {
			spos --;
		}
	}

	if(sel) {
		if(spos == 1) {
			state = State::LevelSelect;
		}
	}
}


