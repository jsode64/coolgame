#pragma once
#include "raylib.h"
#include "buttons.hpp"
#include "game.hpp"
#include <vector>

class OpeningMenu {

	int32_t upkey;
	int32_t downkey;
	int32_t select;

	public:
		OpeningMenu(int sPos, int mPos, int32_t upKey, int32_t downKey, int32_t select);
		int spos;
		int mpos;
		std::vector<Buttons> opening_options;
		void drawButtons(std::vector<Buttons>& buttons);
		void draw(State& state);
		void navigate(State& state);
};