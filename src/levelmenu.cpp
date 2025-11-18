#include "levelmenu.hpp"


Rectangle tb = {160.0f, 110.0f, 50.0f, 20.0f};
Rectangle ob = {160.0f, 150.0f, 100.0f, 20.0f};

Buttons test = Buttons(tb, RED, GREEN, "Test", 1);
Buttons one = Buttons(ob, RED, GREEN, "Level One", 2);

LevelMenu::LevelMenu(int spos, int mpos, int32_t upKey, int32_t downKey, int32_t select) 
	: spos(spos), mpos(mpos), upkey(upKey), downkey(downKey), select(select) {
	level_options.push_back(test);
	level_options.push_back(one);
	choice = 0;
}

void LevelMenu::drawButtons(std::vector<Buttons>& buttons) {
	for (auto& button : buttons) {
		Color currentColor = (spos == button.button_pos) ? button.selectColor : button.color;
		DrawRectangleRec(button.bounds, currentColor);
		DrawText(button.text.c_str(), button.bounds.x, button.bounds.y, 20, BLACK);
	}
}

void LevelMenu::draw(State& state) {
	// To be replaced with texture/image
	DrawRectangle(0, 0, 800, 450, WHITE);
	drawButtons(level_options);
	navigate(state);
}

void LevelMenu::navigate(State& state) {
	bool down = IsKeyPressed(downkey);
	bool up = IsKeyPressed(upkey);
	bool sel = IsKeyPressed(select);

	if(down){
		if(spos >= mpos) {
			spos = 1;
		} else {
			spos ++;
		}
	}

	else if(up) {
		if(spos == 1) {
			spos = 2;
		} else {
			spos --;
		}
	}

	else if(sel) {
		if(spos == 1) {
			choice = 1;
		} else if(spos == 2) {
			choice = 2;
		}
	}
}


