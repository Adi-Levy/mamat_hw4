#include "drawable_list.h"

/*
Iterator member methods implementations
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

void Iterator::increase_counter() {
	if(ptr != nullptr)
		ptr->iterator_counter++;
}

Iterator::Iterator(Node& n) : 
	ptr(&n) 
{ 
	this->increase_counter(); 
}

Iterator::Iterator(const Iterator& other) : 
	ptr(other.ptr) 
{ 
	this->increase_counter(); 
}

Iterator::~Iterator() { this->decrease_counter(); }

Drawable* Iterator::get_object() { return ptr->item; }

void Iterator::invalidate() { ptr->valid = false; }

Iterator& Iterator::set(const Iterator& other) {
	this->decrease_counter();
	ptr = other.ptr;
	this->increase_counter();
	return *this;
}

Iterator& Iterator::next() {
	// tmp is for if we will be deleting this node in decrease_counter 
	// we will still have the next node and not cut the list
	Node* tmp = ptr->next;
	this->decrease_counter();
	ptr = tmp; 
	this->increase_counter();
	// find the next valid node
	while (ptr != nullptr && !this->valid()) {
		this->decrease_counter();
		ptr = ptr->next;
		this->increase_counter();
	}
	// if no more valid nodes return a nonvalid empty Node
	if (!ptr) {
		return this->set(Iterator(*(new Node())));
	}
	return *this;
}

Iterator& Iterator::prev() {
	// tmp is for if we will be deleting this node in decrease_counter 
	// we will still have the next node and not cut the list
	this->decrease_counter();
	ptr = ptr->prev;
	this->increase_counter();
	// find the previous valid node
	while (ptr != nullptr && !this->valid()) {
		this->decrease_counter();
		ptr = ptr->prev;
		this->increase_counter();
	}
	// if no more valid nodes return a nonvalid empty Node
	if (!ptr) {
		return this->set(Iterator(*(new Node())));
	}
	return *this;
}

bool Iterator::valid() const {
	return (!ptr) ? false : ptr->valid;
}


/* 
DrawableList member methods implementations
*/

DrawableList::DrawableList() : size(0) {
	head = nullptr;
	tail = head;
}

DrawableList::~DrawableList() {
	if (size != 0) {
		for (Iterator it = Iterator(*head); it.valid(); it.next()) {
			erase(it);
		}
	}
}

void DrawableList::push_front(Drawable& item) {
	Node* new_node = new Node();
	// check if list is empty
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

void DrawableList::push_back(Drawable& item) {
	Node* new_node = new Node();
	// check if list is empty
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

void DrawableList::erase(Iterator& it) {
	it.invalidate();
	if (it.ptr == head)
		head = head->next;
	else if (it.ptr == tail) {
		tail = tail->prev;
		tail->next = nullptr;
	}
	// reconnect list over the erased node
	else {
		it.ptr->prev->next = it.ptr->next;
		it.ptr->next->prev = it.ptr->prev;
	}
	size--;
}

int DrawableList::get_size() const {
	return size;
}

Iterator DrawableList::begin() {
	Iterator it = Iterator(*head);
	if(it.ptr != nullptr)
		if(!it.valid())
			it.next();
	return it;
}

Iterator DrawableList::end() {
	Iterator it = Iterator(*tail);
	if (it.ptr != nullptr)
		if (!it.valid())
			it.prev();
	return it;
}