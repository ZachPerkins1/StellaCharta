#include "PlayingState.h"

PlayingState::PlayingState(sf::RenderWindow* window): 
	ui(new sf::RenderTexture()),
	game(new sf::RenderTexture()),
	ship(new Ship()) {
	game->create(window->getSize().x, window->getSize().y);
	ui->create(window->getSize().x, window->getSize().y);
	camera = new Camera(game);
	pManager = new PlayerManager(ship, camera);
	TextureMap t;
}

PlayingState::~PlayingState() {
}

void PlayingState::draw(sf::RenderTarget* target) {
	sf::Sprite sp(*TextureMap::getTexture(0, 0));

	ui->clear(sf::Color::Transparent);
	game->clear(sf::Color::Black);

	pManager->update();
	ship->_update();
	camera->update();

	pManager->draw(ui);
	ship->draw(game);

	game->display();
	ui->display();

	sf::Sprite t1(game->getTexture());
	sf::Sprite t2(ui->getTexture());

	target->clear();

	target->draw(t1);
	target->draw(t2);

}

void PlayingState::onEvent(sf::Event event) {
	//if (event.type == sf::Event::MouseButtonPressed)
	//	ship->cTile(event.mouseButton.x, event.mouseButton.y);

	pManager->onEvent(event);
}

void PlayingState::update() {
	pManager->update();
}

