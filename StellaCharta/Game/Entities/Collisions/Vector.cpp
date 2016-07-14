#include "Vector.h"



Vector::Vector(float x, float y) : sf::Vector2f(x, y) {}

Vector::Vector(sf::Vector2f p1, sf::Vector2f p2) :
sf::Vector2f(p2 - p1) {}

Vector::Vector(sf::Vector2f vector) : sf::Vector2f(vector) {}

Vector::Vector() {
}


Vector::~Vector() {
}

float Vector::operator*(const Vector & other) {
	return x * other.x + y * other.y;
}

Vector Vector::operator*(const float & num) {
	return Vector(x * num, y * num);
}

Vector Vector::operator/(const float & num) {
	return Vector(x / num, y / num);
}

float Vector::cross(const Vector& other) {
	return x * other.y - y * other.x;
}

float Vector::magSq() {
	return x*x + y*y;
}

float Vector::mag() {
	return std::sqrt(magSq());
}

bool Vector::isZero() {
	bool xIsZero = abs(x) < 1e-10;
	bool yIsZero = abs(y) < 1e-10;

	return xIsZero && yIsZero;
}



