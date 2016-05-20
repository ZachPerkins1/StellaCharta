#include "PlayerManager.h"
#include "Tiles/TextureMap.h"

PlayerManager::PlayerManager(Ship* ship, Camera* camera): ship(ship), camera(camera) {
	font = new sf::Font();

	if (!font->loadFromFile("resources/fonts/OpenSans-Regular.ttf")) {
		exit(0);
	}

	if (ship != nullptr) {
		camera->setTrackingEnabled(true);
		camera->setTracking(ship);
	}
}


PlayerManager::~PlayerManager() {
	
}

void PlayerManager::draw(sf::RenderTarget* target) {
	
}

void PlayerManager::update() {
	ship->setSelector(selected);
}

void PlayerManager::onEvent(sf::Event e) {
	if (e.type == sf::Event::MouseMoved) {
		select(e.mouseMove.x, e.mouseMove.y);
	} 
	
	if (e.type == sf::Event::MouseWheelScrolled) {
		float delta = e.mouseWheelScroll.delta;
		float scale = 1;
		if (delta < 0)
			scale += 0.1*abs(delta);
		else if (delta > 0)
			scale -= 0.1*delta;

		camera->zoom(scale);
	}
}

void PlayerManager::select(int px, int py) {
	sf::Vector2f coords = camera->mapPixelToCoords(sf::Vector2i(px, py));
	sf::Vector2f rel = ship->mapAbsoluteToRelative(coords);
	if (rel.x != -1)
		selected = ship->mapCoordsToTile(rel);
	else
		selected = sf::Vector2i(-1, -1);


}
