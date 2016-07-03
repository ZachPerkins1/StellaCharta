#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ITrackable.h"

class Camera {
public:
	Camera(sf::RenderTexture* window);
	~Camera();

	void update();

	void setPosition(sf::Vector2f pos);
	void zoom(float scale);
	void setRotation(float rotation);
	void setTracking(ITrackable*);
	void setTrackingEnabled(bool isTracked);

	sf::Vector2f getCenter();
	sf::Vector2f getSize();
	float getRotation();

	sf::Vector2f mapPixelToCoords(sf::Vector2i pos);
	sf::Vector2i mapCoordsToPixel(sf::Vector2f pos);

private:
	sf::RenderTexture* window;

	ITrackable* trackingObject;
	sf::View view;

	bool tracked;
	

};

