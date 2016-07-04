#pragma once
#include "Entities/Ship.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Camera.h"

class World {
public:
	World(Camera* cam);
	~World();
	
	void update();
	void draw(sf::RenderTarget* target);

	void addWorldEntity(WorldEntity* entity);
	WorldEntity* getWorldEntityByIndex(int index);

private:
	struct StarSquare {
		sf::Vector2i coords;
		std::vector<sf::CircleShape> stars;
	};

	std::vector<sf::CircleShape>* starMap;
	std::vector<WorldEntity*> worldMap;


	Camera* camera;

	int STAR_AREA = 50;

};

