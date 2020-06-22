#pragma warning(disable : 4576)
#include "apple.h"

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
Apple::Apple(unsigned short x, unsigned short y) : 
	Drawable::Drawable((struct rect){ x, y, 1, 1 }), draw_flag(false) { }

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
             coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
void Apple::move(direction_t direction) { }

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
             coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
void Apple::draw() {
	if (!draw_flag) {
		mini_gui_print_rect(mg, bounding_box, APPLE);
		draw_flag = true;
	}
}

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
             coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
int Apple::id() {
	return 0;
}

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
             coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
void Apple::refresh() { }

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
             coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
void Apple::step(DrawableList& lst) { }