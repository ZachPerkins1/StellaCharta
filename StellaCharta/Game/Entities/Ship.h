#pragma once

#include "WorldEntity.h"

class Ship : public WorldEntity {
public:
	Ship(float x, float y, int width, int height);
	//TODO: Map(std::string file)

	~Ship();

	void update(float dt);
private:

};