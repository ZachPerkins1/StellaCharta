#include "Collision.h"

Collision::Collision(Entity * a, Entity * b) {
	this->a = a;
	this->b = b;
}

Collision::Collision() {
}

Collision::~Collision() {
}

bool Collision::process() {
	if (detect()) {
		resolve();
		return true;
	}

	return false;
}

bool Collision::detect() {
	hasPoint = false;
	return false;
}

void Collision::resolve() {
}

bool Collision::containsOrigin(std::vector<Vector>* simplex, Vector * ndir) {
	Vector a = simplex->back();
	Vector ao = -a;

	//Line
	if (simplex->size() == 2) {
		Vector b = (*simplex)[0];

		Vector ab = b - a;
		
		// Perpendicular to ab
		*ndir = Vector(-ab.y, ab.x);

		if ((*ndir)*ao < 0)
			*ndir = -*ndir;
	}

	//Triangle
	else {
		Vector b = (*simplex)[1];
		Vector c = (*simplex)[0];

		Vector ab = b - a;
		Vector ac = c - a;

		*ndir = Vector(-ab.y, ab.x);

		if (*ndir * c > 0) {
			*ndir = -*ndir;
		}

		if (*ndir * ao > 0) {
			simplex->erase(simplex->begin());
			return false;
		}

		*ndir = Vector(ac.y, ac.x);

		if (*ndir * b > 0) {
			*ndir = -*ndir;
		}

		if (*ndir * ao > 0) {
			simplex->erase(simplex->begin() + 1);
			return false;
		}

		return true; //inside triangle

	}

	return false;
}

Vector Collision::support(Polygon p1, Polygon p2, Vector sd) {
	Vector a = p1.support(sd);
	Vector b = p2.support(-sd);

	Vector md = a - b;

	return md;
}

Collision::GJKResult Collision::gjk(Polygon p1, Polygon p2) {
	GJKResult result;
	result.intersecting = false;
	if (p1.vertexCount() > 0 && p2.vertexCount() > 0) {
		bool finished = false;
		std::vector<Vector>* simplex = new std::vector<Vector>;

		Vector sd(1, -1); //really any direction
		simplex->push_back(support(p1, p2, sd));

		sd = -sd;

		while (!finished) {
			simplex->push_back(support(p1, p2, sd));

			if ((*simplex)[simplex->size() - 1] * sd > 0) {
				if (containsOrigin(simplex, &sd)) {
					result.intersecting = true;
					finished = true;
				}
			}
			else {
				result.dist = 2;
				result.simplex = *simplex;
				finished = true;
			}
		}

		return result;
	}

	return result;
}
