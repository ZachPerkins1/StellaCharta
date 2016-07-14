#include "Polygon.h"

Polygon::Polygon() {
	points = new std::vector<Vector>;
}


Polygon::~Polygon() {
}

sf::Vector2f Polygon::support(Vector vector) {
	int index = 0;

	if (points->size() > 0) {
		float maxDot = vector * Vector((*points)[0]);

		for (int i = 1; i < points->size(); i++) {
			double dot = vector * Vector((*points)[i]);
			if (dot > maxDot) {
				maxDot = dot;
				index = i;
			}
		}
	}

	return (*points)[index];
}

void Polygon::addPoint(Vector point) {
	points->push_back(point);
}

std::vector<Vector>* Polygon::getPointList() {
	return points;
}

int Polygon::vertexCount() {
	return points->size();
}
