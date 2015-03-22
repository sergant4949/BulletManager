#include "Bullet.h"

Bullet::Bullet(float2 pos, float2 dir, float speed, float time, float life_time):
    position(pos), direction(dir), speed(speed), time(time), lifeTime(life_time) {
    deathTime = time + life_time;
    vectorLength = position.distance(direction);
    if ( vectorLength == 0 ) {
        throw UnknownDirection();
    }
    deltaX = direction.x - position.x;
    deltaY = direction.y - position.y;
    cosAngle = deltaX / vectorLength;
    sinAngle = deltaY / vectorLength;
}

Bullet::~Bullet() {}

const float2 Bullet::getPosition() {
    return position;
}

const float2 Bullet::getDirection() {
    return direction;
}

const float Bullet::getSpeed() {
    return speed;
}

const float Bullet::getTime() {
    return time;
}

const float Bullet::getLifeTime() {
    return lifeTime;
}

const float Bullet::getDeathTime() {
    return deathTime;
}

const float Bullet::getVectorLength() {
    return vectorLength;
}

const float Bullet::getDeltaX() {
    return deltaX;
}

const float Bullet::getDeltaY() {
    return deltaY;
}

const float2 Bullet::getCurrentPosition(float checkTime) {
    float2 cPosition;
    float distance = (checkTime - time) * speed;
    
    cPosition.x = position.x + distance * cosAngle;
    cPosition.y = position.y + distance * sinAngle;
    return cPosition;
}

void Bullet::setPosition(float2 newPosition) {
    position = newPosition;
}

void Bullet::setDirection(float2 newDirection) {
    direction = newDirection;
}

void Bullet::rebound(Wall* cWall, float2 cPos, float time) {
    float sinWall = cWall->getSinAngle();
    float cosWall = cWall->getCosAngle();
    float cosDiff = cosAngle * cosWall + sinAngle * sinWall;
    float tmp = 2 * position.distance(cPos) * cosDiff;
    float x = position.x + tmp * cosWall;
    float y = position.y + tmp * sinWall;

    this->time = time;
    position = cPos;
    direction.x = x;
    direction.y = y;
    vectorLength = position.distance(direction);
    deltaX = direction.x - position.x;
    deltaY = direction.y - position.y;
    cosAngle = deltaX / vectorLength;
    sinAngle = deltaY / vectorLength;
}
