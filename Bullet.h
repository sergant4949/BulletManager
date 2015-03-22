#ifndef BULLET_H
#define BULLET_H

#include <cmath>
#include "float2.h"
#include "Exceptions.h"
#include "Wall.h"

class Bullet {
    private:
        float2 position;
        float2 direction;
        float speed;
        float time;
        float lifeTime;
        float deathTime;
        float vectorLength;
        float deltaX;
        float deltaY;
        float cosAngle;
        float sinAngle;
    public:
        Bullet(float2 pos, float2 dir, float speed, float time, float life_time);
        ~Bullet();

        const float2 getPosition();
        const float2 getDirection();
        const float getSpeed();
        const float getTime();
        const float getLifeTime();
        const float getDeathTime();
        const float getVectorLength();
        const float getDeltaX();
        const float getDeltaY();
        const float2 getCurrentPosition(float checkTime);

        void setPosition(float2 newPosition);
        void setDirection(float2 newDirection);
        void rebound(Wall* cWall, float2 cPos, float time);
};

#endif // BULLET_H