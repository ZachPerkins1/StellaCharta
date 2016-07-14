#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Vector : public sf::Vector2f {
public:
	Vector(float x, float y);
	Vector(sf::Vector2f p1, sf::Vector2f p2);
	Vector(sf::Vector2f vector);
	Vector();
	~Vector();

	float operator*(const Vector& other);
	Vector operator*(const float& num);

	Vector operator/(const float& num);

	float cross(const Vector& other);
	float magSq();
	float mag();

	bool isZero();
};

