#pragma once
#include <SFML/Graphics.hpp>

class Tile {
public:
	Tile(int id, bool solid, sf::Vector2u dim): 
		ID(id), 
		solid(solid), 
		dim(dim),
		sub_id(0) {}

	~Tile() {};

	int getID() { return ID; }
	int getSubID() { return sub_id; }

	void setSubID(int id) { sub_id = id; }

	bool isSolid() { return solid; }

	sf::Vector2u getDimensions() { return dim; }

private:
	int ID;
	bool solid;
	sf::Texture* texture;
	sf::Vector2u dim;

protected:
	int sub_id;
};

