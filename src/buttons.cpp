#include "raylib.h"
#include "buttons.hpp"
#include <vector>


Buttons::Buttons(Rectangle b, Color c, Color sc, std::string t, int b_pos) {
	bounds = b;
	color = c;
	selectColor = sc;
	text = t;
	button_pos = b_pos;
	isSelected = false;
}
