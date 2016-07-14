#include "CollisionBox.h"



CollisionBox::CollisionBox() {
	box = new Line();
}


CollisionBox::~CollisionBox() {
}

Line* CollisionBox::getBox() {
	return box;
}

CollisionBox& CollisionBox::operator=(const CollisionBox& other) {
	if (this != &other) {
			*box = *other.box;
	}

	return *this;
}