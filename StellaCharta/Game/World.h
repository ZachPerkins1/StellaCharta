#pragma once
#include "Entities/Ship.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Camera.h"

class World {
public:
	World(Camera* cam);
	~World();
	
	void update(float dt);
	void draw(sf::RenderTarget* target);

	void addEntity(Entity* entity);
	Entity* getEntityByIndex(int index);

private:
	struct StarSquare {
		sf::Vector2i coords;
		std::vector<sf::CircleShape> stars;
	};

	std::vector<sf::CircleShape>* starMap;
	std::vector<Entity*> worldMap;


	Camera* camera;

	int STAR_AREA = 50;

};

