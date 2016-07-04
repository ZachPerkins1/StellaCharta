#include "WorldEntity.h"

WorldEntity::WorldEntity(float x, float y, int width, int height) : Entity(x, y) {
	tileMap = new Tile**[width];
	floorMap = new Floor**[width];

	collisionMap = new state*[width];

	for (int x = 0; x < width; x++) {
		tileMap[x] = new Tile*[height];
		collisionMap[x] = new state[height];
		floorMap[x] = new Floor*[height];

		for (int y = 0; y < height; y++) {
			floorMap[x][y] = new Floor();
			tileMap[x][y] = nullptr;
		}
	}

	texture = new sf::RenderTexture();
	texture->create(width*PIX, height*PIX);

	setOrigin(sf::Vector2f(texture->getSize().x / 2, texture->getSize().y / 2));

	this->width = width;
	this->height = height;

	refreshDimensions();

	selector = sf::Vector2i(-1, -1);

	floorMap[0][0]->setSubID(1);
}


WorldEntity::~WorldEntity() {
}

void WorldEntity::draw(sf::RenderTarget * target) {
	texture->clear();

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			renderTile(floorMap[x][y], x, y);
			renderTile(tileMap[x][y], x, y);
		}
	}

	if (selector.x != -1)
		drawSelector(selector.x, selector.y);

	texture->display();
	setTexture(texture->getTexture());
	target->draw(*this);
}

void WorldEntity::_update() {
	update();
}

sf::Vector2f WorldEntity::getTrackingPos() {
	return getPosition();
}

float WorldEntity::getTrackingAngle() {
	return getRotation();
}

void WorldEntity::setSelector(sf::Vector2i pos) {
	selector = pos;
}

void WorldEntity::renderTile(Tile* tile, int x, int y) {
	if (tile != nullptr) {
		float px = x*PIX;
		float py = y*PIX;
		sf::Sprite spr(*TextureMap::getTexture(tile));
		spr.setPosition(sf::Vector2f(px, py));
		texture->draw(spr);
	}
}

void WorldEntity::drawSelector(int x, int y) {
	float px = x*PIX;
	float py = y*PIX;
	sf::RectangleShape rect(sf::Vector2f(PIX, PIX));
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(-2);
	rect.setOutlineColor(sf::Color::Yellow);
	rect.setPosition(px, py);
	texture->draw(rect);
}

sf::Vector2f WorldEntity::mapAbsoluteToRelative(sf::Vector2f coords) {
	sf::Vector2f center = getPosition();
	double dist = sqrt(pow(coords.x - center.x, 2) + pow(coords.y - center.y, 2));

	if (dist <= lenDiag) {
		Corners c = getCorners();

		sf::Vector2f topPoint = util::nearestPoint(coords, c.ul, c.ur);
		sf::Vector2f leftPoint = util::nearestPoint(coords, c.ul, c.ll);

		if (util::liesOnSegment(topPoint, c.ul, c.ur, 0.1) && util::liesOnSegment(leftPoint, c.ul, c.ll, 0.1)) {
			return sf::Vector2f(util::dist(leftPoint, coords), util::dist(topPoint, coords));
		}
	}

	return sf::Vector2f(-1, -1);
}

sf::Vector2f WorldEntity::mapRelativeToAbsolute(sf::Vector2f coords) {
	return sf::Vector2f();
}

sf::Vector2i WorldEntity::mapCoordsToTile(sf::Vector2f coords) {
	int x = ((int)coords.x) / PIX;
	int y = ((int)coords.y) / PIX;
	return sf::Vector2i(x, y);
}

sf::Vector2f WorldEntity::mapTileToCoords(sf::Vector2i coords) {
	double x = coords.x * PIX;
	double y = coords.y * PIX;
	return sf::Vector2f(x, y);
}

WorldEntity::Corners WorldEntity::getCorners() {
	sf::Vector2f center = getPosition();
	Corners corners;
	double theta = getRotation() + angDiag;

	if (theta > 360)
		theta -= 360;

	double dx = -(lenDiag * cos(DEG_TO_RAD * theta));
	double dy = -(lenDiag * sin(DEG_TO_RAD * theta));
	corners.ul = sf::Vector2f(center.x + dx, center.y + dy);

	theta = getRotation();
	double r_theta = theta * DEG_TO_RAD;

	dx = (width*PIX) * cos(r_theta);
	dy = ((width*PIX) * sin(r_theta));

	corners.ur = sf::Vector2f(corners.ul.x + dx, corners.ul.y + dy);

	dx = -((height*PIX) * sin(r_theta));
	dy = (height*PIX) * cos(r_theta);

	corners.ll = sf::Vector2f(corners.ul.x + dx, corners.ul.y + dy);

	return corners;
}

void WorldEntity::refreshDimensions() {
	double hw = (width*PIX) / 2;
	double hh = (height*PIX) / 2;

	lenDiag = sqrt(pow(hw, 2) + pow(hh, 2));
	angDiag = RAD_TO_DEG * atan(hh / hw);
}



