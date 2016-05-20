#pragma once
#include "../Util.h"
#include "Tiles/Tile.h"
#include "Tiles/TextureMap.h"
#include "Tiles/Floor.h"
#include <cmath>
#include "ITrackable.h"

#define M_PI 3.141592653589793238462643383279502884197169399375105820974

class Ship : sf::Sprite, public ITrackable {
public:
	Ship();
	//TODO: Map(std::string file)

	~Ship();

	struct state {
		bool occupied = false;
		sf::Vector2u* coords = nullptr;
	};

	struct Corners {
		sf::Vector2f ur;
		sf::Vector2f ll;
		sf::Vector2f ul;
	};

	void update();
	void draw(sf::RenderTarget* target);

	bool hasFloor(int x, int y);

	virtual sf::Vector2f getTrackingPos();
	void setSelector(sf::Vector2i pos);

	sf::Vector2i mapCoordsToTile(sf::Vector2f coords);
	sf::Vector2f mapTileToCoords(sf::Vector2i coords);

	sf::Vector2f mapAbsoluteToRelative(sf::Vector2f coords);
	sf::Vector2f mapRelativeToAbsolute(sf::Vector2f coords);


private:
	void renderTile(Tile* tile, int x, int y);
	void drawSelector(int x, int y);

	void refreshDimensions();
	Corners getCorners();
	
	int width = 15;
	int height = 20;

	int PIX = 32;

	const double DEG_TO_RAD = M_PI / 180;
	const double RAD_TO_DEG = 180 / M_PI;

	double lenDiag;
	double angDiag;
	
	Tile*** tileMap;
	Floor*** floorMap;

	state** collisionMap;

	sf::Vector2i selector;

	sf::RenderTexture* texture;
};

