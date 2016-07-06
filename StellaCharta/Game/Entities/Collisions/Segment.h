#pragma once
#include <SFML/Graphics.hpp>
#include "../../../Util.h"

class Segment {
public:
	Segment(sf::Vector2f p1, sf::Vector2f p2);
	~Segment();

	bool intersects(Segment s, sf::Vector2f* intersection);

	sf::Vector2f p1;
	sf::Vector2f p2;

};

