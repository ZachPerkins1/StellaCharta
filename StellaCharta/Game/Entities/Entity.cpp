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

void Entity::setMass(double mass) {
	this->mass = mass;
}

void Entity::addMass(double mass) {
	this->mass += mass;
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

double Entity::getMass() {
	return mass;
}

void Entity::moveEntity(float dt) {
	this->move(sf::Vector2f(dx*dt*Tile::SIZE, dy*dt*Tile::SIZE));
	this->rotate(drot*dt);
}
