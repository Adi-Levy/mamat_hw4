#pragma warning(disable : 4576)

#include "monster.h"
#include "drawable_list.h"


Monster::Monster(unsigned short x, unsigned short y, int direction_hold) : 
	Drawable::Drawable((struct rect) { x, y, 1, 1 }), level(1), vel(1), 
	current_direction(left), direction_hold(direction_hold), direction_counter(0), 
	next_bb{ x, y, 1, 1 } , gfx(MONSTER0) { }

void Monster::move(direction_t direction) {
	// Get world size
	struct rect world_size = mini_gui_get_screen_size(mg);
	if (direction_counter == 0) {
		current_direction = direction;
		direction_counter = direction_hold;
	}
	switch (current_direction)
	{
	case up: 
		if (bounding_box.y - vel >= 0) 
			next_bb.y = bounding_box.y - vel;
		break;
	case down:
		if (bounding_box.y + bounding_box.height + vel < world_size.height)
			next_bb.y = bounding_box.y + vel;
		break;
	case left: 
		if (bounding_box.x - vel >= 0)
			next_bb.x = bounding_box.x - vel;
		break;
	case right:
		if (bounding_box.x + bounding_box.width + vel < world_size.width)
			next_bb.x = bounding_box.x + vel;
		break;
	default:
		break;
	}
	direction_counter--;
}

void Monster::draw() {
	mini_gui_print_rect(mg, bounding_box, gfx);
}

int Monster::id() {
	return (int)monster;
}

void Monster::refresh() {
	if (level < 5) {
		gfx = MONSTER0;
		vel = 1;
		next_bb.width = 1;
		next_bb.height = 1;
	}
	else if (level < 15) {
		gfx = MONSTER1;
		vel = 1;
		next_bb.width = 3;
		next_bb.height = 1;
	}
	else if (level < 25) {
		gfx = MONSTER2;
		vel = 1;
		next_bb.width = 3;
		next_bb.height = 2;
	}
	else {
		gfx = MONSTER3;
		vel = 2;
		next_bb.width = 8;
		next_bb.height = 3;
	}
	// Get world size
	struct rect world_size = mini_gui_get_screen_size(mg);
	// Fix position in case of screen overflow
	if (next_bb.x + next_bb.width >= world_size.width) {
		next_bb.x = world_size.width - next_bb.width;
	}
	if (next_bb.y + next_bb.height >= world_size.height) {
		next_bb.y = world_size.height - next_bb.height;
	}
}

void Monster::step(DrawableList& lst) {
	for (Iterator it = lst.begin(); it.valid(); it.next()) {
		bounding_box = next_bb;
		if (collide(*(it.get_object()))) {
			if (it.get_object()->id() == apple) {
				level += 1;
				lst.erase(it);
			}
			else {
				if (this != it.get_object()) {
					int other_lvl = dynamic_cast<Monster*>(it.get_object())->level;
					if (other_lvl > 0) {
						if (level > other_lvl) {
							level += other_lvl;
							lst.erase(it);
						}
						else {
							dynamic_cast<Monster*>(it.get_object())->level += level;
							delete_me(lst);
							return;
						}
					}
				}
			}
			refresh();
		}
	}
	bounding_box = next_bb;
}

void Monster::delete_me(DrawableList& lst) {
	Iterator it = lst.begin();
	while (this != it.get_object()) {
		it.next();
	}
	lst.erase(it);
}