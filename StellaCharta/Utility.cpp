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

sf::Vector2f utility::nearestPoint(sf::Vector2f p1, sf::Vector2f l1, sf::Vector2f l2) {
	double y1 = l1.y;
	double y2 = l2.y;
	double x1 = l1.x;
	double x2 = l2.x;

	double x3 = p1.x;
	double y3 = p1.y;

	sf::Vector2f point;

	double k = ((y2 - y1) * (x3 - x1) - (x2 - x1) * (y3 - y1)) / (pow(y2 - y1, 2) + pow(x2 - x1, 2));
	point.x = x3 - k * (y2 - y1);
	point.y = y3 + k * (x2 - x1);

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

//Graham scan to find points
std::vector<sf::Vector2f> utility::convexHull(std::vector<sf::Vector2f> points) {
	int n = points.size();

	if (n < 3)
		return std::vector<sf::Vector2f>();

	std::vector<sf::Vector2f> hull;

	//Find point w/ lowest x and y
	int lowest = 0;
	for (int i = 1; i < n; i++) {
		sf::Vector2f l = points[lowest];
		sf::Vector2f p = points[i];

		if (p.y > l.y) {
			lowest = i;
		}
		else if (p.y == l.y) {
			if (p.x < l.x) {
				lowest = i;
			}
		}
	}

	sf::Vector2f tmp = points[0];
	points[0] = points[lowest];
	points[lowest] = tmp;

	//Sort points based on polar angle from point 0
	for (int i = 1; i < n; i++) {
		for (int q = 1; q < n; q++) {
			sf::Vector2f a = points[i];
			sf::Vector2f b = points[q];

			float islopea = (a.x - points[0].x) / (a.y - points[0].y);
			float islopeb = (b.x - points[0].x) / (b.y - points[0].y);

			if (islopea > islopeb) {
				points[q] = a;
				points[i] = b;
			}
		}
	}

	hull.push_back(points[0]);
	hull.push_back(points[1]);
	hull.push_back(points[2]);
	n = points.size();

	int hi = 2;
	for (int i = 3; i < n; i++) {
		sf::Vector2f a = hull[hi - 1];
		sf::Vector2f b = hull[hi];
		sf::Vector2f c = points[i];

		while (getOrientation(hull[hi - 1], hull[hi], points[i]) != utility::COUNTER_CLOCKWISE) {
			hull.pop_back();
			hi--;
		}

		hull.push_back(points[i]);
		hi++;
	}

	
	return hull;
}

