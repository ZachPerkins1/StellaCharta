#include "CollisionBox.h"



CollisionBox::CollisionBox() {
}


CollisionBox::~CollisionBox() {
}

void CollisionBox::addLine(Line l) {
	lines.push_back(l);
}

void CollisionBox::appendLast(sf::Vector2f point) {
	Line last = lines[lines.size() - 1];
	Line next(last.p2, point);
	addLine(next);
}

void CollisionBox::finishLines() {
	Line first = lines[0];
	Line last = lines[lines.size() - 1];
	Line next(first.p1, last.p2);
	addLine(next);
}
