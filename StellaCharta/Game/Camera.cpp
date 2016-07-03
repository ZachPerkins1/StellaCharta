#include "Camera.h"

Camera::Camera(sf::RenderTexture* window): 
	window(window) {
	view = window->getDefaultView();
}

Camera::~Camera() {
}

void Camera::update() {
	if (tracked) {
		setPosition(trackingObject->getTrackingPos());
		setRotation(trackingObject->getTrackingAngle());
	}

	window->setView(view);
}

void Camera::setPosition(sf::Vector2f pos) {
	view.setCenter(pos);
}

void Camera::zoom(float scale) {
	view.zoom(scale);
}

void Camera::setRotation(float rotation) {
	view.setRotation(rotation);
}

void Camera::setTracking(ITrackable* object) {
	trackingObject = object;
}

void Camera::setTrackingEnabled(bool isTracked) {
	tracked = isTracked;
}

sf::Vector2f Camera::getCenter() {
	return window->getView().getCenter();
}

sf::Vector2f Camera::getSize() {
	return window->getView().getSize();
}

float Camera::getRotation() {
	return window->getView().getRotation();
}

sf::Vector2f Camera::mapPixelToCoords(sf::Vector2i pos) {
	return window->mapPixelToCoords(pos);
}

sf::Vector2i Camera::mapCoordsToPixel(sf::Vector2f pos) {
	return window->mapCoordsToPixel(pos);
}

