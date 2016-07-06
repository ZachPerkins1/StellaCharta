#pragma once
#include "Entity.h"

#define M_PI 3.141592653589793238462643383279502884197169399375105820974

//Represents something inside of a SpaceEntity
class WorldEntity : public ITrackable, public Entity {
public:
	WorldEntity(float x, float y, int width, int height);
	~WorldEntity();

	void draw(sf::RenderTarget* target);
	void _update(float dt);
	virtual void update(float dt) = 0;

	virtual sf::Vector2i mapCoordsToTile(sf::Vector2f coords);
	virtual sf::Vector2f mapTileToCoords(sf::Vector2i coords);

	void setSelector(sf::Vector2i pos);

	virtual sf::Vector2f getTrackingPos();
	virtual float getTrackingAngle();

	struct state {
		bool occupied = false;
		sf::Vector2u* coords = nullptr;
	};

private:
	void renderTile(Tile* tile, int x, int y);
	void drawSelector(int x, int y);

	const int PIX = Tile::SIZE;

	double lenDiag;
	double angDiag;

	Tile*** tileMap;
	Floor*** floorMap;
	state** collisionMap;

	int width;
	int height;

	sf::Vector2i selector;

	sf::RenderTexture* texture;
};