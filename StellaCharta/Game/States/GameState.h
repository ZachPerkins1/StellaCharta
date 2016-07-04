#pragma once
#include <SFML/Graphics.hpp>

class GameState {
public:
	GameState();
	~GameState();
	
	virtual void draw(sf::RenderTarget* target) = 0;
	virtual void update(float dt) = 0;
	virtual void onEvent(sf::Event) = 0;
};

