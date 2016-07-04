#include "World.h"

World::World(Camera* cam) :
	starMap(new std::vector<sf::CircleShape>),
	worldMap(std::vector<Entity*>()),
	camera(cam) {
}


World::~World() {
}

void World::update(float dt) {
	for (int i = 0; i < worldMap.size(); i++) {
		worldMap[i]->_update(dt);
	}
}

void World::draw(sf::RenderTarget* target) {
	for (int i = 0; i < worldMap.size(); i++) {
		worldMap[i]->draw(target);
	}
}

void World::addEntity(Entity* entity) {
	worldMap.push_back(entity);
}

Entity* World::getEntityByIndex(int index) {
	return worldMap[index];
}