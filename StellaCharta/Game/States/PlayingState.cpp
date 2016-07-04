#include "PlayingState.h"

PlayingState::PlayingState(sf::RenderWindow* window): 
	ui(new sf::RenderTexture()),
	game(new sf::RenderTexture()) {
	game->create(window->getSize().x, window->getSize().y);
	ui->create(window->getSize().x, window->getSize().y);
	camera = new Camera(game);
	
	world->addWorldEntity(new Ship())
	pManager = new PlayerManager(world->getWorldEntityByIndex(0), camera);
	TextureMap t;

	ship->setPosition(100, 100);
	ship2->setPosition(300, 200);
}

PlayingState::~PlayingState() {
}

void PlayingState::draw(sf::RenderTarget* target) {
	sf::Sprite sp(*TextureMap::getTexture(0, 0));

	ui->clear(sf::Color::Transparent);
	game->clear(sf::Color::Black);

	pManager->draw(ui);
	ship->draw(game);
	ship2->draw(game);

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
	ship->rotate(0.2);
	pManager->update();
	ship->_update();
	ship2->_update();
	camera->update();
}

