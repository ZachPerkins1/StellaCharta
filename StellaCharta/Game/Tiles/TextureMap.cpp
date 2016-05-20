#include "TextureMap.h"
#include <sstream>

std::vector<std::vector<sf::Texture*>> TextureMap::map;

TextureMap::TextureMap() {
	map = std::vector<std::vector<sf::Texture*>>();
	add("floor.png");
}


TextureMap::~TextureMap() {

}

sf::Texture * TextureMap::getTexture(int id, int sub) {
	sf::Texture* t;
	try {
		t = map[id][sub];
	} catch (...) {
		t = nullptr;
	}

	return t;
}

sf::Texture * TextureMap::getTexture(Tile* tile) {
	return getTexture(tile->getID(), tile->getSubID());
}

int TextureMap::add(std::string filepath) {
	// Load image so we can check its height
	sf::Image* i = new sf::Image();
	std::ostringstream ss;

	// Always in textures folder
	ss << "resources/textures/" << filepath;
	std::string path = ss.str();
	i->loadFromFile(path);
	
	// Height of image
	int w = i->getSize().x;
	int h = i->getSize().y;

	delete i;

	std::vector<sf::Texture*> vec;
	for (int x = 0; x < w; x += h) {
		sf::Texture* text = new sf::Texture;
		text->loadFromFile(path, sf::IntRect(x, 0, h, h));
		vec.push_back(text);
	}

	map.push_back(vec);
	return map.size() - 1;
}
