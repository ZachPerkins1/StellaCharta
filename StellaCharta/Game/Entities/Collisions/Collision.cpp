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
	/*
	hasPoint = false;

	Vector vRel = b->getVelocity() - a->getVelocity();
	double t = 0;
	Vector dist = gjkDistance();
	double distMag = dist.mag();

	while (distMag > 1 && t < 1) {
		double velocityBound = (vRel*(dist / distMag) + (abs(a->getdrot())*ra) + abs(b->getdrot())*rb));
		double delta = distMag / velocityBound;

		a->moveEntity(delta);
		 
		dist = gjkDistance();
		distMag = dist.mag();
		
	}

	*/

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

Vector Collision::closestPointToOrigin(Vector a, Vector b) {
	Vector v = utility::nearestPointOnSegment(Vector(0, 0), a, b);
	return v;
}

Vector Collision::support(Polygon p1, Polygon p2, Vector sd) {
	Vector a = p1.support(sd);
	Vector b = p2.support(-sd);

	Vector md = a - b;

	return md;
}

bool Collision::gjkIntersection(Polygon p1, Polygon p2) {
	if (p1.vertexCount() > 0 && p2.vertexCount() > 0) {
		std::vector<Vector>* simplex = new std::vector<Vector>;

		Vector sd(1, -1); //really any direction
		simplex->push_back(support(p1, p2, sd));

		sd = -sd;

		while (true) {
			simplex->push_back(support(p1, p2, sd));

			if ((*simplex)[simplex->size() - 1] * sd > 0) {
				if (containsOrigin(simplex, &sd)) {
					return true;
				}
			}
			else {
				return false;
			}
		}

	}
}

Vector Collision::gjkDistance(Polygon p1, Polygon p2) {
	if (p1.vertexCount() > 2 && p2.vertexCount() > 2) {
		Vector a;
		Vector b;
		Vector c;

		Vector sd(1, -1); //really any direction

		a = support(p1, p2, sd);
		sd = -sd;
		b = support(p1, p2, sd);

		sd = closestPointToOrigin(a, b);

		while (true) {
			sd = -sd;
			if (sd.isZero())
				return sf::Vector2f(0, 0);

			c = support(p1, p2, sd);

			//Our last try
			//double aMag = a.mag();
			//Vector sdScaled = sd / aMag;

			double da = a * sd;


			// Our current try
			double dc = c * sd;

			//Difference between the tries
			double diff = dc - da;

			if (diff < TOLERANCE) {
				return sd;
			}

			Vector p1 = closestPointToOrigin(a, c);
			Vector p2 = closestPointToOrigin(c, b);

			if (p1.magSq() < p2.magSq()) {
				b = c;
				sd = p1;
			}
			else {
				a = c;
				sd = p2;
			}
		}
	}
}
