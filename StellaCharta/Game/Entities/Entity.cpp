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

sf::Vector2f Entity::mapAbsoluteToRelative(sf::Vector2f coords) {
	sf::Vector2f center = getPosition();
	double dist = sqrt(pow(coords.x - center.x, 2) + pow(coords.y - center.y, 2));

	if (dist <= lenDiag) {
		Corners c = getCorners();

		sf::Vector2f topPoint = util::nearestPoint(coords, c.ul, c.ur);
		sf::Vector2f leftPoint = util::nearestPoint(coords, c.ul, c.ll);

		if (util::liesOnSegment(topPoint, c.ul, c.ur, 0.1) && util::liesOnSegment(leftPoint, c.ul, c.ll, 0.1)) {
			return sf::Vector2f(util::dist(leftPoint, coords), util::dist(topPoint, coords));
		}
	}

	return sf::Vector2f(-1, -1);
}

sf::Vector2f Entity::mapRelativeToAbsolute(sf::Vector2f coords) {
	sf::Vector2f point = getCorners().ul;

	double theta = DEG_TO_RAD * getRotation();

	double dx1 = (coords.x * cos(theta));
	double dy1 = (coords.x * sin(theta));

	double x1 = point.x + dx1;
	double y1 = point.y + dy1;

	double dx2 = (coords.y * sin(theta));
	double dy2 = (coords.y * cos(theta));

	double x2 = x1 - dx2;
	double y2 = y1 + dy2;

	return sf::Vector2f(x2, y2);
}

Entity::Corners Entity::getCorners() {
	sf::Vector2f center = getPosition();
	Corners corners;
	double theta = getRotation() + angDiag;

	double width = getLocalBounds().width;
	double height = getLocalBounds().height;

	if (theta > 360)
		theta -= 360;

	double dx = -(lenDiag * cos(DEG_TO_RAD * theta));
	double dy = -(lenDiag * sin(DEG_TO_RAD * theta));
	corners.ul = sf::Vector2f(center.x + dx, center.y + dy);

	theta = getRotation();
	double r_theta = theta * DEG_TO_RAD;

	dx = (width) * cos(r_theta);
	dy = ((width) * sin(r_theta));

	corners.ur = sf::Vector2f(corners.ul.x + dx, corners.ul.y + dy);

	dx = -((height) * sin(r_theta));
	dy = (height) * cos(r_theta);

	corners.ll = sf::Vector2f(corners.ul.x + dx, corners.ul.y + dy);

	return corners;
}

void Entity::refreshDimensions() {
	double width = getLocalBounds().width;
	double height = getLocalBounds().height;

	double hw = (width) / 2;
	double hh = (height) / 2;

	lenDiag = sqrt(pow(hw, 2) + pow(hh, 2));
	angDiag = RAD_TO_DEG * atan(hh / hw);
}

CollisionBox Entity::getMesh() {
	return mesh;
}

CollisionBox Entity::getAdjustedMesh() {
	CollisionBox c = mesh;
	Line* l = c.getBox();
	for (int i = 0; i < l->getPointAmount(); i++) {
		(*l)[i] = mapRelativeToAbsolute((*l)[i]);
	}

	return c;
}