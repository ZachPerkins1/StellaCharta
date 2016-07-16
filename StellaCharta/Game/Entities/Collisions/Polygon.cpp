#include "Polygon.h"

Polygon::Polygon() {
	points = new std::vector<Vector>;
}


Polygon::~Polygon() {
}

Polygon Polygon::createFromPoints(std::vector<Vector> points) {
	Polygon p;
	for (int i = 0; i < points.size(); i++) {
		p.addPoint(points[i]);
	}

	return p;
}

Polygon Polygon::convexHull() {
	std::vector<Vector> points = *(this->points);
	int n = points.size();

	if (n < 3)
		return Polygon();

	std::vector<Vector> hull;

	//Find point w/ lowest x and y
	int lowest = 0;
	for (int i = 1; i < n; i++) {
		Vector l = points[lowest];
		Vector p = points[i];

		if (p.y > l.y) {
			lowest = i;
		}
		else if (p.y == l.y) {
			if (p.x < l.x) {
				lowest = i;
			}
		}
	}

	Vector tmp = points[0];
	points[0] = points[lowest];
	points[lowest] = tmp;

	//Sort points based on polar angle from point 0
	for (int i = 1; i < n; i++) {
		for (int q = 1; q < n; q++) {
			Vector a = points[i];
			Vector b = points[q];

			float islopea = (a.x - points[0].x) / (a.y - points[0].y);
			float islopeb = (b.x - points[0].x) / (b.y - points[0].y);

			if (islopea > islopeb) {
				points[q] = a;
				points[i] = b;
			}
		}
	}

	hull.push_back(points[0]);

	int s = 2;

	for (int i = 1; i < n; i++) {
		if (utility::getOrientation(hull[0], points[i], points[i + 1]) == utility::COUNTER_CLOCKWISE) {
			hull.push_back(points[i]);
			hull.push_back(points[i + 1]);
			s = i + 2;
			break;
		}
	}

	n = points.size();

	int hi = 2;
	for (int i = s; i < n; i++) {
		sf::Vector2f a = hull[hi - 1];
		sf::Vector2f b = hull[hi];
		sf::Vector2f c = points[i];

		while (utility::getOrientation(hull[hi - 1], hull[hi], points[i]) != utility::COUNTER_CLOCKWISE) {
			hull.pop_back();
			hi--;
		}

		hull.push_back(points[i]);
		hi++;
	}


	return Polygon::createFromPoints(hull);
}

Polygon Polygon::add(Polygon p) {
	Polygon sum;

	for (int a = 0; a < this->vertexCount(); a++) {
		for (int b = 0; b < p.vertexCount(); b++) {
			sum.addPoint(getPoint(a) + p.getPoint(b));
		}
	}

	return sum.convexHull();
}

Polygon Polygon::subtract(Polygon p) {
	Polygon diff;

	for (int a = 0; a < this->vertexCount(); a++) {
		for (int b = 0; b < p.vertexCount(); b++) {
			diff.addPoint(getPoint(a) - p.getPoint(b));
		}
	}

	return diff.convexHull();
}

Polygon Polygon::combine(Polygon p) {
	Polygon com;

	for (int i = 0; i < this->vertexCount(); i++) {
		com.addPoint(this->getPoint(i));
	}

	for (int i = 0; i < p.vertexCount(); i++) {
		com.addPoint(p.getPoint(i));
	}

	return com;
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

Vector Polygon::getPoint(int index) {
	return (*points)[index];
}

int Polygon::vertexCount() {
	return points->size();
}
