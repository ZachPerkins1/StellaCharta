#pragma once
#include <SFML/System.hpp>

namespace util {
	double dist(sf::Vector2f p1, sf::Vector2f p2);
	bool liesOnSegment(sf::Vector2f p1, sf::Vector2f s1, sf::Vector2f s2, double tolerance);
	sf::Vector2f nearestPoint(sf::Vector2f p1, sf::Vector2f l1, sf::Vector2f l2);
}