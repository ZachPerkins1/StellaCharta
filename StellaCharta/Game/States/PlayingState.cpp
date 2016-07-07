#include "PlayingState.h"

PlayingState::PlayingState(sf::RenderWindow* window): 
	ui(new sf::RenderTexture()),
	game(new sf::RenderTexture()) {
	game->create(window->getSize().x, window->getSize().y);
	ui->create(window->getSize().x, window->getSize().y);
	camera = new Camera(game);

	world = new World(camera);
	world->addEntity(new Ship(100, 400, 5, 5));
	world->addEntity(new Ship(900, 400, 5, 5));
	pManager = new PlayerManager((Ship*)(world->getEntityByIndex(0)), camera);
	TextureMap t;

	world->getEntityByIndex(0)->rotate(20);
	world->getEntityByIndex(0)->setdx(5);
	world->getEntityByIndex(1)->setdx(-5);
	//world->getEntityByIndex(1)->setdx(-10);
}

PlayingState::~PlayingState() {
}

void PlayingState::draw(sf::RenderTarget* target) {
	sf::Sprite sp(*TextureMap::getTexture(0, 0));

	ui->clear(sf::Color::Transparent);
	game->clear(sf::Color::Black);

	camera->setPosition(sf::Vector2f(0, 0));

	for (int i = 0; i < points.size(); i++) {
		sf::CircleShape c(1);
		c.setFillColor(sf::Color::Red);
		c.setPosition(points[i]);
		game->draw(c);
	}

	std::vector<sf::Vector2f> hull = utility::convexHull(points);
	
	for (int i = 0; i < hull.size(); i++) {
		sf::CircleShape c(1);
		c.setFillColor(sf::Color::Green);
		c.setPosition(hull[i]);
		game->draw(c);
	}

	pManager->draw(ui);
	world->draw(game);

	game->display();
	ui->display();

	sf::Sprite t1(game->getTexture());
	sf::Sprite t2(ui->getTexture());

	target->clear();

	target->draw(t1);
	target->draw(t2);

}

void PlayingState::onEvent(sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed)
		points.push_back(camera->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));


	pManager->onEvent(event);
}

void PlayingState::update(float dt) {
	pManager->update(dt);
	world->update(dt);
	camera->update(dt);
}

