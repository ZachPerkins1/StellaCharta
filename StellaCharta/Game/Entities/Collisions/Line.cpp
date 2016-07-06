#include "Line.h"

std::vector<Segment> Line::getSegments() {
	std::vector<Segment> segments;

	for (int i = 0; i < getPointAmount() - 1; i++) {
		segments.push_back(Segment(points[i], points[i+1]));
	}

	return segments;
}

void Line::addPoint(sf::Vector2f point) {
	points.push_back(point);
}

void Line::addPoint(float x, float y) {
	addPoint(sf::Vector2f(x, y));
}

int Line::getPointAmount() {
	return points.size();
}

bool Line::has(sf::Vector2f point) {
	for (int i = 0; i < getPointAmount(); i++) {
		if (points[i] == point)
			return true;
	}

	return false;
}

sf::Vector2f& Line::operator[](int index) {
	return points[index];
}