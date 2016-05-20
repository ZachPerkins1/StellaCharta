#pragma once
#include "Ship.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Camera.h"

class World {
public:
	World(Camera* cam);
	~World();
	
	void update();
	void draw(sf::RenderTarget* target);

private:
	struct StarSquare {
		sf::Vector2i coords;
		std::vector<sf::CircleShape> stars;
	};

	std::vector<sf::CircleShape>* starMap;
	std::vector<Ship>* shipMap;

	Camera* camera;

	int STAR_AREA = 50;

};

