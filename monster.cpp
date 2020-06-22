#pragma warning(disable : 4576)

#include "monster.h"
#include "drawable_list.h"

Monster::Monster(unsigned short x, unsigned short y, int direction_hold) : 
	Drawable::Drawable((struct rect) { x, y, 1, 1 }), level(1), vel(1), 
	current_direction(left), direction_hold(direction_hold), direction_counter(0), 
	next_bb{ x, y, 1, 1 } , gfx(MONSTER0) { }

Monster::Monster(const Monster& other) :
	Drawable::Drawable(other.bounding_box), level(other.level), vel(other.vel),
	current_direction(other.current_direction), direction_hold(other.direction_hold), 
	direction_counter(other.direction_counter), next_bb(other.next_bb), gfx(other.gfx) { }

void Monster::move(direction_t direction) {
	// Get world size
	struct rect world_size = mini_gui_get_screen_size(mg);
	if (direction_counter == 0) {
		//change direction and reset hold counter
		current_direction = direction;
		direction_counter = direction_hold;
	}
	switch (current_direction)
	{
	case up: 
		if (bounding_box.y - vel > 0) 
			next_bb.y = bounding_box.y - vel;
		break;
	case down:
		if (bounding_box.y + bounding_box.height + vel < world_size.height)
			next_bb.y = bounding_box.y + vel;
		break;
	case left: 
		if (bounding_box.x - vel > 0)
			next_bb.x = bounding_box.x - vel;
		break;
	case right:
		if (bounding_box.x + bounding_box.width + vel < world_size.width)
			next_bb.x = bounding_box.x + vel;
		break;
	default:
		break;
	}
	//safeguards from direction hold of 0
	if(direction_counter != 0)
		direction_counter--;
}

void Monster::draw() {
	mini_gui_clear_rect(mg, bounding_box);
	mini_gui_print_rect(mg, next_bb, gfx);
	bounding_box = next_bb;
}

int Monster::id() {
	return 1;
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
		// self check
		if (this != it.get_object()) {
			if (collide(*(it.get_object()))) {
				// check if objects colideed with is an apple
				if (it.get_object()->id() == 0) {
					level += 1;
					lst.erase(it);
				}
				// if colided and not with apple then it colided with monster
				else {
					Monster* other = dynamic_cast<Monster*>(it.get_object());
					if (other->level > 0) {
						if (level > other->level) {
							level += other->level;
							lst.erase(it);
						}
						else {
							other->level += level;
							other->refresh();
							// other monster won so delete me and exit this function
							delete_me(lst);
							return;
						}
					}
				}
			}
		}
	}
	// after going through all objects on screen and checking collision and updating level
	// update next_bb
	refresh();
}

void Monster::delete_me(DrawableList& lst) {
	Iterator it = lst.begin();
	while (this != it.get_object()) {
		it.next();
	}
	lst.erase(it);
}