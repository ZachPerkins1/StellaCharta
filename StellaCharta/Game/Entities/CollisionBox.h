#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Line {
public:
	sf::Vector2f p1;
	sf::Vector2f p2;

	Line(sf::Vector2f p1, sf::Vector2f p2) :
		p1(p1),
		p2(p2) {
	}
};


class CollisionBox {
public:
	CollisionBox();
	~CollisionBox();

	void addLine(Line l);
	void appendLast(sf::Vector2f point);
	void finishLines();

private:
	double width;
	double height;

	std::vector<Line> lines;
};
