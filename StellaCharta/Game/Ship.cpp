#include "Ship.h"

Ship::Ship() : WorldEntity(15, 20) {
	setPosition(500, 400);
	//setRotation(34);
}

Ship::~Ship() {
}

void Ship::update() {
	rotate(5);
}