#include "Util.h"

double util::dist(sf::Vector2f p1, sf::Vector2f p2) {
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

bool util::liesOnSegment(sf::Vector2f p1, sf::Vector2f s1, sf::Vector2f s2, double tolerance = 0.1) {
	double len = dist(s1, s2);
	double pLen = dist(p1, s1) + dist(p1, s2);

	if (abs(pLen - len) > tolerance)
		return false;

	return true;
}

sf::Vector2f util::nearestPoint(sf::Vector2f p1, sf::Vector2f l1, sf::Vector2f l2) {
	double y1 = l1.y;
	double y2 = l2.y;
	double x1 = l1.x;
	double x2 = l2.x;

	double x3 = p1.x;
	double y3 = p1.y;

	sf::Vector2f point;

	double k = ((y2 - y1) * (x3 - x1) - (x2 - x1) * (y3 - y1)) / (pow(y2 - y1, 2) + pow(x2 - x1, 2));
	point.x = x3 - k * (y2 - y1);
	point.y = y3 + k * (x2 - x1);

	return point;
}