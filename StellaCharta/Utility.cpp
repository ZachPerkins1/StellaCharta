#include "Utility.h"

double utility::dist(sf::Vector2f p1, sf::Vector2f p2) {
	return sqrt(distSq(p1, p2));
}

double utility::distSq(sf::Vector2f p1, sf::Vector2f p2) {
	return pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2);
}

bool utility::liesOnSegment(sf::Vector2f p1, sf::Vector2f s1, sf::Vector2f s2, double tolerance = 0.1) {
	double len = dist(s1, s2);
	double pLen = dist(p1, s1) + dist(p1, s2);

	if (abs(pLen - len) > tolerance)
		return false;

	return true;
}

sf::Vector2f utility::nearestPointOnLine(sf::Vector2f p, sf::Vector2f a, sf::Vector2f b) {
	Vector ab = b - a;
	Vector ap = p - a;

	double distAB = dist(a, b);
	Vector abs = ab / distAB;
	Vector aps = ap / distAB;

	double scale = vecDotProduct(abs, aps);

	Vector point = (ab * scale) + a;

	return point;
}

sf::Vector2f utility::nearestPointOnSegment(sf::Vector2f p, sf::Vector2f a, sf::Vector2f b) {
	Vector ab = b - a;
	Vector ap = p - a;

	double distAB = dist(a, b);
	Vector abs = ab / distAB;
	Vector aps = ap / distAB;

	double scale = vecDotProduct(abs, aps);

	if (scale > 1) {
		scale = 1;
	}

	if (scale < 0) {
		scale = 0;
	}

	Vector point = (ab * scale) + a;

	return point;
}

double utility::vecCrossProduct(sf::Vector2f v1, sf::Vector2f v2) {
	return v1.x * v2.y - v1.y * v2.x;
}

double utility::vecDotProduct(sf::Vector2f v1, sf::Vector2f v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

bool utility::segmentIntersects(sf::Vector2f l1, sf::Vector2f l2, sf::Vector2f l3, sf::Vector2f l4, sf::Vector2f* result) {
	sf::Vector2f intersection;
	result = nullptr;

	sf::Vector2f r = l2 - l1;
	sf::Vector2f s = l4 - l3;
	double rxs = vecCrossProduct(r, s);
	double qpxr = vecCrossProduct(l3 - l1, r);

	// If r x s = 0 and (q - p) x r = 0, then the two lines are collinear.
	if (abs(rxs) < EPSILON && abs(qpxr) < EPSILON) {
		// 1. If either  0 <= (q - p) * r <= r * r or 0 <= (p - q) * s <= * s
		// then the two lines are overlapping,
		if ((0 <= vecDotProduct((l3 - l1), r) && vecDotProduct((l3 - l1), r) <= vecDotProduct(r, r)) || (0 <= vecDotProduct((l1 - l3), s) && vecDotProduct((l1 - l3), s) <= vecDotProduct(s, s)))
			return true;

		// 2. If neither 0 <= (q - p) * r = r * r nor 0 <= (p - q) * s <= s * s
		// then the two lines are collinear but disjoint.
		// No need to implement this expression, as it follows from the expression above.
		return false;
	}

	// 3. If r x s = 0 and (q - p) x r != 0, then the two lines are parallel and non-intersecting.
	if (abs(rxs) < EPSILON && !(abs(qpxr) < EPSILON))
		return false;

	// t = (q - p) x s / (r x s)
	double t = vecCrossProduct((l3 - l1), s) / rxs;

	// u = (q - p) x r / (r x s)

	double u = vecCrossProduct(l3 - l1, r) / rxs;

	// 4. If r x s != 0 and 0 <= t <= 1 and 0 <= u <= 1
	// the two line segments meet at the point p + t r = q + u s.
	if (!(abs(rxs) < EPSILON) && (0 <= t && t <= 1) && (0 <= u && u <= 1)) {
		// We can calculate the intersection point using either t or u.
		intersection = l1 + sf::Vector2f(r.x*t, r.y*t);
		result = &intersection;

		// An intersection was found.
		return true;
	}

	// 5. Otherwise, the two line segments are not parallel but do not intersect.
	return false;
}

utility::Orientation utility::getOrientation(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3) {
	double k = (p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x);
	if (k == 0) return utility::COLLINEAR;
	else if (k < 0) return utility::CLOCKWISE;
	else return utility::COUNTER_CLOCKWISE;
}
