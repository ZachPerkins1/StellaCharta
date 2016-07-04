#pragma once
#include "Entities/Ship.h"
#include "Camera.h"
#include <sstream>

class PlayerManager {
public:
	PlayerManager(WorldEntity* ship, Camera* camera);
	~PlayerManager();

	void draw(sf::RenderTarget*);
	void update(float dt);

	void onEvent(sf::Event e);

private:
	WorldEntity* ship;
	Camera* camera;

	sf::Font* font;

	sf::Vector2i selected;

	void select(int px, int py);

};

