#pragma once
#include "../Entity.h"
#include "Polygon.h"

class Collision {
public:
	Collision(Entity* a, Entity* b);
	Collision();
	~Collision();

	bool process();
	bool detect();
	void resolve();

	Vector support(Polygon p1, Polygon p2, Vector sd);

	bool containsOrigin(std::vector<Vector>* simplex, Vector* ndir);
	Vector closestPointToOrigin(Vector a, Vector b);

	bool gjkIntersection(Polygon p1, Polygon p2);
	Vector gjkDistance(Polygon p1, Polygon p2);

private:

	Entity* a;
	Entity* b;

	sf::Vector2f collisionPoint;
	bool hasPoint = false;

	const double TOLERANCE = 10;

};

