#include "World.h"

World::World(Camera* cam) :
	starMap(new std::vector<sf::CircleShape>),
	shipMap(new std::vector<Ship>),
	camera(cam) {
}


World::~World() {
}

void World::update() {

}

void World::draw(sf::RenderTarget* target) {
}
