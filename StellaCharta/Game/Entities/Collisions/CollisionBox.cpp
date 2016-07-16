#include "CollisionBox.h"



CollisionBox::CollisionBox() {
	box = new Line();
}


CollisionBox::~CollisionBox() {
}

Polygon CollisionBox::getConvexHull() {
	Polygon result;

	for (int i = 0; i < convexComponents.size(); i++) {
		result = result.combine(convexComponents[i]);
	}

	return result.convexHull();
}

Polygon CollisionBox::getConvexComponentByID(int id) {
	return convexComponents[id];
}
