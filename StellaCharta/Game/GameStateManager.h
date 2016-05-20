#pragma once

#include "States/PlayingState.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "States/GameState.h"
#include <iostream>
#include <chrono>
#include <thread>

class GameStateManager {
public:
	GameStateManager();
	~GameStateManager();

private:
	sf::RenderWindow* window;
	bool running = true;

	int currState;
	GameState** states;
	const int STATE_COUNT = 1;

	void initWindow();
	void startLoop();

};

