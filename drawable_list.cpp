#include "drawable_list.h"

/*
Iterator member methods implementations
*/
/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
void Iterator::decrease_counter() {
	if (ptr != nullptr) {
		ptr->iterator_counter--;
		if (ptr->iterator_counter == 0 && !ptr->valid) {
			delete ptr->item;
			delete ptr;
			ptr = nullptr;
		}
	}
}

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
void Iterator::increase_counter() {
	if(ptr != nullptr)
		ptr->iterator_counter++;
}

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
Iterator::Iterator(Node& n) : 
	ptr(&n) 
{ 
	this->increase_counter(); 
}

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
Iterator::Iterator(const Iterator& other) : 
	ptr(other.ptr) 
{ 
	this->increase_counter(); 
}

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
Iterator::~Iterator() { this->decrease_counter(); }

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
Drawable* Iterator::get_object() { return ptr->item; }

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
void Iterator::invalidate() { ptr->valid = false; }

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
Iterator& Iterator::set(const Iterator& other) {
	if(ptr != nullptr)
		this->decrease_counter();
	ptr = other.ptr;
	if (ptr != nullptr)
		this->increase_counter();
	return *this;
}

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
Iterator& Iterator::next() {
	Node* tmp = ptr->next;
	this->decrease_counter();
	ptr = tmp; 
	this->increase_counter();
	while (ptr != nullptr && !this->valid()) {
		this->decrease_counter();
		ptr = ptr->next;
		this->increase_counter();
	}
	if (!ptr) {
		return this->set(Iterator(*(new Node())));
	}
	return *this;
}

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
Iterator& Iterator::prev() {
	this->decrease_counter();
	ptr = ptr->prev;
	this->increase_counter();
	while (ptr != nullptr && !this->valid()) {
		this->decrease_counter();
		ptr = ptr->prev;
		this->increase_counter();
	}
	if (!ptr) {
		return this->set(Iterator(*(new Node())));
	}
	return *this;
}

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
bool Iterator::valid() const {
	return (!ptr) ? false : ptr->valid;
}


/* 
DrawableList member methods implementations
*/
/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
DrawableList::DrawableList() : size(0) {
	head = nullptr;
	tail = head;
}

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
DrawableList::~DrawableList() {
	if (size != 0) {
		for (Iterator it = Iterator(*head); it.valid(); it.next()) {
			erase(it);
		}
	}
}

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
void DrawableList::push_front(Drawable& item) {
	Node* new_node = new Node();
	if (head != nullptr) {
		new_node->next = head;
		head->prev = new_node;
	}
	else
		tail = new_node;
	head = new_node;
	new_node->item = &item;
	new_node->valid = true;
	size++;
}

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
void DrawableList::push_back(Drawable& item) {
	Node* new_node = new Node();
	if (tail != nullptr) {
		new_node->prev = tail;
		tail->next = new_node;
	}
	else 
		head = new_node;
	tail = new_node;
	new_node->item = &item;
	new_node->valid = true;
	size++;
}

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
void DrawableList::erase(Iterator& it) {
	it.invalidate();
	if (it.ptr == head)
		head = head->next;
	else if (it.ptr == tail) {
		tail = tail->prev;
		tail->next = nullptr;
	}
	else {
		it.ptr->prev->next = it.ptr->next;
		it.ptr->next->prev = it.ptr->prev;
	}
	size--;
}

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
int DrawableList::get_size() const {
	return size;
}

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
Iterator DrawableList::begin() {
	Iterator it = Iterator(*head);
	if(it.ptr != nullptr)
		if(!it.valid())
			it.next();
	return it;
}

/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
Iterator DrawableList::end() {
	Iterator it = Iterator(*tail);
	if (it.ptr != nullptr)
		if (!it.valid())
			it.prev();
	return it;
}