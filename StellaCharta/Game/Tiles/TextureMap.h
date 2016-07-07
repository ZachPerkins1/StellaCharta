#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include "Tile.h"

class TextureMap {
public:
	TextureMap();
	~TextureMap();

	static std::vector<std::vector<sf::Texture*>> map;
	static sf::Texture* getTexture(int id, int sub);
	static sf::Texture* getTexture(Tile* tile);
	static int add(std::string filepath);
};

