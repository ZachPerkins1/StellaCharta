#pragma once
#include <SFML/Graphics.hpp>
#include "Polygon.h"

class CollisionBox {
public:
	CollisionBox();
	~CollisionBox();

	Polygon getConvexHull();
	Polygon getConvexComponentByID(int id);

private:
	double width;
	double height;

	std::vector<Polygon> convexComponents;


};
