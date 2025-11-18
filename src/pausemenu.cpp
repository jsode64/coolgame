#include "pausemenu.hpp"



Rectangle eb = {160.0f, 110.0f, 40.0f, 20.0f};
Rectangle cb = {160.0f, 150.0f, 90.0f, 20.0f};


Buttons exit_button = Buttons(eb, RED, GREEN, "Exit", 1);
Buttons cont_button = Buttons(cb, RED, GREEN, "Continue", 2);

PauseMenu::PauseMenu(int spos, int mpos, int32_t upKey, int32_t downKey, int32_t select) 
					: spos(spos), mpos(mpos), upkey(upKey), downkey(downKey), select(select) {
	options.push_back(exit_button);
	options.push_back(cont_button);
}

void PauseMenu::drawButtons(std::vector<Buttons>& buttons) {
	for (auto& button : buttons) {
	Color currentColor = (spos == button.button_pos) ? button.selectColor : button.color;
	DrawRectangleRec(button.bounds, currentColor);
	DrawText(button.text.c_str(), button.bounds.x, button.bounds.y, 20, BLACK);
	}
}
	

void PauseMenu::draw(State& state) {
	// To be replaced with texture/image
DrawRectangle(150, 100, 500, 300, WHITE);
drawButtons(options);
navigate(state);
}

void PauseMenu::navigate(State& state) {
	bool down = IsKeyPressed(downkey);
	bool up = IsKeyPressed(upkey);
	bool sel = IsKeyPressed(select);
	if(down) {
		if(spos >= mpos) {
			spos = 1;
		}

		else {
			spos ++;
		}
	}

	else if(up) {
		if(spos == 1) {
			spos = 2;
		}

		else {
			spos --;
		}
	}

	else if(sel) {
		if(spos == 1) {
			state = State::Opening;
		}

		else if(spos == 2) {
			state = State::Playing;
		}
	}

}

	
