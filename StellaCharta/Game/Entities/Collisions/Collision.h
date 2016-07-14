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

	struct GJKResult {
		bool intersecting;
		float dist;
		std::vector<Vector> simplex;
	};

	bool containsOrigin(std::vector<Vector>* simplex, Vector* ndir);
	Vector support(Polygon p1, Polygon p2, Vector sd);
	GJKResult gjk(Polygon p1, Polygon p2);

private:
	Entity* a;
	Entity* b;

	sf::Vector2f collisionPoint;
	bool hasPoint = false;

};

