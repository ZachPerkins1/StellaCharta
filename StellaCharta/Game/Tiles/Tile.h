#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionTile.h"
#include <vector>

class Tile {
public:
	Tile(int id, bool solid, sf::Vector2u dim, CollisionTile* cTile): 
		ID(id), 
		solid(solid), 
		cTile(cTile),
		dim(dim),
		sub_id(0) {}

	~Tile() {};

	int getID() { return ID; }
	int getSubID() { return sub_id; }

	void setSubID(int id) { sub_id = id; }

	bool isSolid() { return solid; }

	sf::Vector2u getDimensions() { return dim; }

	static const int SIZE = 32;

private:
	int ID;
	bool solid;
	CollisionTile* cTile;
	sf::Texture* texture;
	sf::Vector2u dim;

protected:
	int sub_id;
};
