#pragma once
#include <SFML/Graphics.hpp>
#include "Segment.h"

class Line {
public:
	Line();

	void addPoint(sf::Vector2f point);
	void addPoint(float x, float y);

	int getPointAmount();

	bool has(sf::Vector2f point);

	sf::Vector2f& operator[](int index);
	std::vector<Segment> getSegments();

	std::vector<sf::Vector2f> getPoints();

private:
	std::vector<sf::Vector2f> points;
};
