#pragma once
#include "../Ship.h"
#include "GameState.h"
#include "../PlayerManager.h"
#include "../Camera.h"

class PlayingState : public GameState {
public:
	PlayingState(sf::RenderWindow* window);
	~PlayingState();

	virtual void draw(sf::RenderTarget*);
	virtual void update();
	virtual void onEvent(sf::Event);

private:
	Ship* ship;
	PlayerManager* pManager;
	Camera* camera;

	sf::RenderTexture* ui;
	sf::RenderTexture* game;
};

