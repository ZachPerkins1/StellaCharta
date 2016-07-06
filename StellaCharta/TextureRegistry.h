#pragma once
#include <SFML/Graphics.hpp>

class TextureRegistry {
public:
	static TextureRegistry* instance;

	static TextureRegistry* getInstance() {
		if (instance == nullptr)
			instance = new TextureRegistry();
		return instance;
	}

	TextureRegistry();
	~TextureRegistry();
};

class Texture {
public:
	Texture();
	~Texture();

	int id = -1;

private:
	sf::Texture* texture;


};