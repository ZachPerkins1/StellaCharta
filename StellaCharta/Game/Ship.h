#pragma once

#include "Entities/WorldEntity.h"

class Ship : public WorldEntity {
public:
	Ship();
	//TODO: Map(std::string file)

	~Ship();

	void update();
private:

};