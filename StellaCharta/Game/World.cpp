#include "World.h"

World::World(Camera* cam) :
	starMap(new std::vector<sf::CircleShape>),
	worldMap(std::vector<WorldEntity*>()),
	camera(cam) {
}


World::~World() {
}

void World::update() {
	for (int i = 0; i < worldMap.size(); i++) {
		worldMap[i]->_update();
	}
}

void World::draw(sf::RenderTarget* target) {
	for (int i = 0; i < worldMap.size(); i++) {
		worldMap[i]->draw(target);
	}
}

void World::addWorldEntity(WorldEntity* entity) {
	worldMap.push_back(entity);
}

WorldEntity* World::getWorldEntityByIndex(int index) {
	return worldMap[index];
}