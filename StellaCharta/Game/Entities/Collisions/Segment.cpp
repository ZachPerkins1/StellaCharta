#include "Segment.h"

Segment::Segment(sf::Vector2f p1, sf::Vector2f p2) {
	this->p1 = p1;
	this->p2 = p2;
}


Segment::~Segment() {
}

bool Segment::intersects(Segment s, sf::Vector2f* intersection) {
	return utility::segmentIntersects(p1, p2, s.p1, s.p2, intersection);
}