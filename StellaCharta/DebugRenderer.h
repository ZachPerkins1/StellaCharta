#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Game/Entities/Collisions/Polygon.h"

namespace drender {
	void drawShape(sf::RenderTarget* targ, std::vector<Vector> vertices, sf::Color color);
	void drawShape(sf::RenderTarget* targ, std::vector<Vector> vertices);

	void drawPoints(sf::RenderTarget* targ, std::vector<Vector> vertices, sf::Color color);
	void drawPoints(sf::RenderTarget* targ, std::vector<Vector> vertices);

};