#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "../../../Utility.h"

class Polygon {
public:
	Polygon();
	~Polygon();

	static Polygon createFromPoints(std::vector<Vector> points);

	Polygon convexHull();
	Polygon add(Polygon p); 
	Polygon subtract(Polygon p);

	Polygon combine(Polygon p);

	sf::Vector2f support(Vector vector);

	void addPoint(Vector point);
	std::vector<Vector>* getPointList();
	Vector getPoint(int index);
	int vertexCount();

	//WARNING: Brute forces the search - Only use if a collision is sure-fire.
	//         Use the collision class for a more efficient method of collision
	//         Detection.
	bool intersects(Polygon p, Vector* intersectionPoint);

private:
	std::vector<Vector>* points;
	
};

