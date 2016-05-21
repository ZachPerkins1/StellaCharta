#pragma once
#include <SFML/System.hpp>

class IWorld {
public:
	IWorld() {}
	~IWorld() {}
	
	virtual sf::Vector2f mapAbsoluteToRelative(sf::Vector2f coords) = 0;
	virtual sf::Vector2f mapRelativeToAbsolute(sf::Vector2f coords) = 0;

	virtual sf::Vector2i mapCoordsToTile(sf::Vector2f coords) = 0;
	virtual sf::Vector2f mapTileToCoords(sf::Vector2i coords) = 0;

	virtual sf::Vector2f doCollision(float radius, sf::Vector2f coords) = 0;

};

