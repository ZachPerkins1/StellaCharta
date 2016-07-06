#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Line.h"

class CollisionBox {
public:
	CollisionBox();
	~CollisionBox();

	Line* getBox();

private:
	double width;
	double height;

	Line* box;
};
