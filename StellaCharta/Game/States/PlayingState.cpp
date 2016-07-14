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

	//world->getEntityByIndex(0)->rotate(20);
	//world->getEntityByIndex(0)->setdx(5);
	//world->getEntityByIndex(1)->setdx(-5);
	//world->getEntityByIndex(1)->setdx(-10);
}

PlayingState::~PlayingState() {
}

void PlayingState::draw(sf::RenderTarget* target) {
	sf::Sprite sp(*TextureMap::getTexture(0, 0));

	ui->clear(sf::Color::Transparent);
	game->clear(sf::Color::Black);

	camera->setPosition(sf::Vector2f(0, 0));

	Polygon triangle;

	triangle.addPoint(sf::Vector2f(62, 32));
	triangle.addPoint(sf::Vector2f(50, 10));
	triangle.addPoint(sf::Vector2f(21, 14));

	drender::drawShape(game, *(triangle.getPointList()));
	drender::drawShape(game, *(shape.getPointList()), sf::Color::Blue);
	drender::drawPoints(game, std::vector<Vector> {Vector(0, 0)}, sf::Color::Yellow);

	//std::vector<sf::Vector2f> hull = utility::convexHull(points);

	//drender::drawShape(game, hull, sf::Color::Green);

	if (shape.getPointList()->size() > 3) {
		drender::drawShape(game, utility::minkowskiDifference(*(triangle.getPointList()), *(shape.getPointList())));
	}

	Collision c;
	Collision::GJKResult res = c.gjk(shape, triangle);
	drender::drawShape(game, res.simplex, sf::Color::Red);

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
		shape.addPoint(camera->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));


	pManager->onEvent(event);
}

void PlayingState::update(float dt) {
	pManager->update(dt);
	world->update(dt);
	camera->update(dt);
}

