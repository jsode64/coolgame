#pragma once
#include "raylib.h"
#include <string>
#include <vector>

enum class State;

struct Buttons {
	Rectangle bounds;
	Color color;
	Color selectColor;
	std::string text;
	int button_pos;
	bool isSelected;

	Buttons(Rectangle b, Color c, Color sc, std::string t, int b_pos);
};