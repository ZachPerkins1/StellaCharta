#pragma once
#include <SFML/System.hpp>

namespace util {
	double dist(sf::Vector2f p1, sf::Vector2f p2);
	bool liesOnSegment(sf::Vector2f p1, sf::Vector2f s1, sf::Vector2f s2, double tolerance);
	sf::Vector2f nearestPoint(sf::Vector2f p1, sf::Vector2f l1, sf::Vector2f l2);

	
	double vecCrossProduct(sf::Vector2f v1, sf::Vector2f v2);
	double vecDotProduct(sf::Vector2f v1, sf::Vector2f v2);

	bool segmentIntersects(sf::Vector2f l1, sf::Vector2f l2, sf::Vector2f l3, sf::Vector2f l4, sf::Vector2f* result);

	const double EPSILON = 1e-10;
}