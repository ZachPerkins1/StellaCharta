#pragma once
#include <SFML/Graphics.hpp>
#include "Line.h"

class CollisionBox {
public:
	CollisionBox();
	~CollisionBox();

	Line* getBox();
	CollisionBox& CollisionBox::operator=(const CollisionBox& other);

private:
	double width;
	double height;

	Line* box;
};
