#pragma once
#include "../Entities/Ship.h"
#include "GameState.h"
#include "../PlayerManager.h"
#include "../Camera.h"
#include "../World.h"
#include "../../DebugRenderer.h"
#include "../Entities/Collisions/Collision.h"

class PlayingState : public GameState {
public:
	PlayingState(sf::RenderWindow* window);
	~PlayingState();

	virtual void draw(sf::RenderTarget*);
	virtual void update(float dt);
	virtual void onEvent(sf::Event);

private:
	World* world;
	PlayerManager* pManager;
	Camera* camera;

	sf::RenderTexture* ui;
	sf::RenderTexture* game;

	Polygon shape;
	sf::Uint32 count = 0;
};

