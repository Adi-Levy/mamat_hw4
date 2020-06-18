#pragma warning(disable : 4576)
#include "apple.h"

Apple::Apple(unsigned short x, unsigned short y) : 
	Drawable::Drawable((struct rect){ x, y, 1, 1 }), draw_flag(false) { }

void Apple::move(direction_t direction) { }

void Apple::draw() {
	if (!draw_flag) {
		mini_gui_print_rect(mg, bounding_box, APPLE);
		draw_flag = true;
	}
}

int Apple::id() {
	return (int)apple;
}

void Apple::refresh() { }

void Apple::step(DrawableList& lst) { }