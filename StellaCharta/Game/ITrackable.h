#pragma once
#include <SFML/Graphics.hpp>

class ITrackable {
public:
	ITrackable() {};
	~ITrackable() {};

	virtual sf::Vector2f getTrackingPos() = 0;

};

