#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Game/Entities/Collisions/Vector.h"

namespace utility {
	enum Orientation {
		COLLINEAR = 0,
		CLOCKWISE = 1,
		COUNTER_CLOCKWISE = 2
	};

	double dist(sf::Vector2f p1, sf::Vector2f p2);
	double distSq(sf::Vector2f p1, sf::Vector2f p2);

	bool liesOnSegment(sf::Vector2f p1, sf::Vector2f s1, sf::Vector2f s2, double tolerance);

	sf::Vector2f nearestPointOnLine(sf::Vector2f p1, sf::Vector2f l1, sf::Vector2f l2);
	sf::Vector2f nearestPointOnSegment(sf::Vector2f p1, sf::Vector2f l1, sf::Vector2f l2);

	double vecCrossProduct(sf::Vector2f v1, sf::Vector2f v2);
	double vecDotProduct(sf::Vector2f v1, sf::Vector2f v2);

	bool segmentIntersects(sf::Vector2f l1, sf::Vector2f l2, sf::Vector2f l3, sf::Vector2f l4, sf::Vector2f* result);

	Orientation getOrientation(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3);

	const double EPSILON = 1e-10;
};