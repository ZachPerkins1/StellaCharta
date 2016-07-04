#include "Entity.h"

Entity::Entity(float x, float y) {
	setPosition(x, y);
	dx = 0;
	dy = 0;
	drot = 0;
}

Entity::~Entity() {
}

void Entity::setdx(double dx) {
	this->dx = dx;
}

void Entity::setdy(double dy) {
	this->dy = dy;
}

void Entity::setdrot(double drot) {
	this->drot = drot;
}

double Entity::getdx() {
	return dx;
}

double Entity::getdy() {
	return dy;
}

double Entity::getdrot() {
	return drot;
}

void Entity::moveEntity(float dt) {
	this->move(sf::Vector2f(dx*dt*32, dy*dt*32));
	this->rotate(drot*dt);
}
