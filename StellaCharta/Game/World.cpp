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
		checkCollisions(i, dt);
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

void World::checkCollisions(int index, float dt) {
	Entity* e1 = worldMap[index];
	e1->moveEntity(dt);
	sf::FloatRect r1f = e1->getGlobalBounds();
	e1->moveEntity(-dt);
	sf::FloatRect r1i = e1->getGlobalBounds();

	sf::FloatRect brect1 = formBoundingRect(r1f, r1i);

	for (int i = index+1; i < worldMap.size(); i++) {
		Entity* e2 = worldMap[i];
		e2->moveEntity(dt);
		sf::FloatRect r2f = e2->getGlobalBounds();
		e2->moveEntity(-dt);
		sf::FloatRect r2i = e2->getGlobalBounds();

		sf::FloatRect brect2 = formBoundingRect(r2f, r2i);

		if (brect1.intersects(brect2)) {
			processCollision(e1, e2, dt);
		}

		//if (worldMap[index]->getGlobalBounds().intersects(worldMap[i]->getGlobalBounds())) {
		//	processCollision(worldMap[i], worldMap[index], dt);
		//}
	}
}

void World::processCollision(Entity* e1, Entity* e2, float dt) {
	e1->moveEntity(-dt);
	
}

sf::FloatRect World::formBoundingRect(sf::FloatRect r1, sf::FloatRect r2) {
	float left = std::min(r1.left, r2.left);
	float top = std::min(r1.top, r2.top);
	float right = std::max(r1.left + r1.width, r2.left + r2.width);
	float bottom = std::max(r1.top + r1.height, r2.top + r2.height);

	return sf::FloatRect(left, top, right - left, bottom - top);
}
