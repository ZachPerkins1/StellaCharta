#pragma once
#include <SFML/Graphics.hpp>
#include "../../Util.h"
#include "../Tiles/Tile.h"
#include "../Tiles/TextureMap.h"
#include "../Tiles/Floor.h"
#include <cmath>
#include "../ITrackable.h"
#include "../IWorld.h"

class Entity : public sf::Sprite {
public:
	Entity(float x, float y);
	~Entity();

	void setdx(double dx);
	void setdy(double dy);
	void setdrot(double drot);

	double getdx();
	double getdy();
	double getdrot();

	void moveEntity();

private:
	double dx;
	double dy;
	double drot;

};

