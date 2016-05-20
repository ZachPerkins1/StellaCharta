#pragma once
#include "Ship.h"
#include "Camera.h"
#include <sstream>

class PlayerManager {
public:
	PlayerManager(Ship* ship, Camera* camera);
	~PlayerManager();

	void draw(sf::RenderTarget*);
	void update();

	void onEvent(sf::Event e);

private:
	Ship* ship;
	Camera* camera;

	sf::Font* font;

	sf::Vector2i selected;

	void select(int px, int py);

};

