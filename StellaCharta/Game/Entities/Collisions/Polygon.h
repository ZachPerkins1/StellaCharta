#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Vector.h"

class Polygon {
public:
	Polygon();
	~Polygon();

	sf::Vector2f support(Vector vector);
	void addPoint(Vector point);

	std::vector<Vector>* getPointList();

	int vertexCount();

private:
	std::vector<Vector>* points;
	
};

