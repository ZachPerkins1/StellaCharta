#pragma once
#include "Collisions/CollisionBox.h"
#include <SFML/Graphics.hpp>
#include "../Tiles/Tile.h"
#include "../Tiles/TextureMap.h"
#include "../Tiles/Floor.h"
#include <cmath>
#include "../ITrackable.h"
#include "../IWorld.h"

#define M_PI 3.141592653589793238462643383279502884197169399375105820974

class Entity : public sf::Sprite {
public:
	Entity(float x, float y);
	~Entity();

	void setdx(double dx);
	void setdy(double dy);

	void setdrot(double drot);

	void setMass(double mass);
	void addMass(double mass);

	double getdx();
	double getdy();

	double getdrot();

	double getMass();

	void moveEntity(float dt);

	virtual void draw(sf::RenderTarget* target) = 0;
	virtual void _update(float dt) = 0;

	virtual sf::Vector2f mapAbsoluteToRelative(sf::Vector2f coords);
	virtual sf::Vector2f mapRelativeToAbsolute(sf::Vector2f coords);

	CollisionBox getMesh();
	CollisionBox getAdjustedMesh();

	
private:
	double lenDiag;
	double angDiag;

	double dx; // m/s
	double dy;

	double drot; // deg/s

	double mass; // kg

	const double DEG_TO_RAD = M_PI / 180;
	const double RAD_TO_DEG = 180 / M_PI;

	CollisionBox mesh;

protected:
	struct Corners {
		sf::Vector2f ur;
		sf::Vector2f ll;
		sf::Vector2f ul;
	};

	Corners getCorners();
	void refreshDimensions();

};