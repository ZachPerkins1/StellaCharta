#include "DebugRenderer.h"

void drender::drawShape(sf::RenderTarget* targ, std::vector<Vector> vertices, sf::Color color) {
	const int size = vertices.size();
	std::vector<sf::Vertex> v;

	for (int i = 0; i < vertices.size(); i++) {
		sf::Vertex vertex(vertices[i], color);
		v.push_back(vertex);
	}

	if (size > 0)
		v.push_back(v[0]);

	targ->draw(v.data(), v.size(), sf::LinesStrip);
	
	sf::Color colors[] = { sf::Color::Blue, sf::Color::Green, sf::Color::Yellow };
	v.clear();
	for (int i = 0; i < vertices.size(); i++) {
		sf::Color color = i < 3 ? colors[i] : sf::Color::Red;
		sf::Vertex vertex(vertices[i], color);
		v.push_back(vertex);
	}

	targ->draw(v.data(), v.size(), sf::Points);

}

void drender::drawShape(sf::RenderTarget * targ, std::vector<Vector> vertices) {
	drawShape(targ, vertices, sf::Color::White);
}

void drender::drawPoints(sf::RenderTarget * targ, std::vector<Vector> vertices, sf::Color color) {
	const int size = vertices.size();
	std::vector<sf::Vertex> v;

	for (int i = 0; i < vertices.size(); i++) {
		sf::Vertex vertex(vertices[i], color);
		v.push_back(vertex);
	}

	targ->draw(v.data(), v.size(), sf::Points);
}

void drender::drawPoints(sf::RenderTarget * targ, std::vector<Vector> vertices) {
	drawPoints(targ, vertices, sf::Color::White);
}

