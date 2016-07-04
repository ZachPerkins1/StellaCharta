#include "GameStateManager.h"

GameStateManager::GameStateManager(): window(
	new sf::RenderWindow(sf::VideoMode(1000, 750), 
	"Generic City Game", 
	sf::Style::Titlebar | sf::Style::Close)) {
	states = new GameState*[STATE_COUNT]{new PlayingState(window)};
	initWindow();
	currState = 0;
}

GameStateManager::~GameStateManager() {
	delete window;
}

void GameStateManager::initWindow() {
	window->setVisible(true);
	startLoop();
}

void GameStateManager::startLoop() {
	while (window->isOpen()) {
		sf::Clock clock;
		sf::Event e;
		while (window->pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window->close();
			}
			else {
				states[currState]->onEvent(e);
			}
		}

		states[currState]->update(dt);
		states[currState]->draw(window);

		window->display();

		dt = clock.getElapsedTime().asSeconds();

		//std::this_thread::sleep_for(std::chrono::milliseconds(wait >= 0 ? wait : 0));

	}
}
