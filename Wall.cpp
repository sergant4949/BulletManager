#include "Wall.h"

unsigned Wall::lastId = 0;
std::map<unsigned, Wall*>* Wall::wallsList = new std::map<unsigned, Wall*>();

Wall::Wall(float2 first, float2 second): firstCorner(first), secondCorner(second) {
    length = firstCorner.distance(secondCorner);
    if ( length == 0 ) {
        throw WallWithZeroLength();
    }
    deltaX = secondCorner.x - firstCorner.x;
    deltaY = secondCorner.y - firstCorner.y;
    cosAngle = deltaX / length;
    sinAngle = deltaY / length;
    lastId += 1;
    id = lastId;
    wallsList->insert(std::pair<unsigned, Wall*>(id, this));
}

Wall::~Wall() {
    wallsList->erase(id);
}

std::map<unsigned, Wall*>* Wall::getWallsList() {
    return wallsList;
}

const unsigned Wall::getId() const {
    return id;
}

const float2 Wall::getFirstCorner() const {
    return firstCorner;
}

const float2 Wall::getSecondCorner() const {
    return secondCorner;
}

const float Wall::len() {
    return length;
}

const float Wall::getDeltaX() {
    return deltaX;
}

const float Wall::getDeltaY() {
    return deltaY;
}

const float Wall::getCosAngle() {
    return cosAngle;
}

const float Wall::getSinAngle() {
    return sinAngle;
}
