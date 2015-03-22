#ifndef WALL_H
#define WALL_H

#include <map>
#include "float2.h"
#include "Exceptions.h"

class Wall {
    private:
        unsigned id;

        static unsigned lastId;
        static std::map<unsigned, Wall*>* wallsList;

        float2 firstCorner;
        float2 secondCorner;
        float length;
        float deltaX;
        float deltaY;
        float cosAngle;
        float sinAngle;
    public:
        Wall(float2 first, float2 second);
        ~Wall();

        static std::map<unsigned, Wall*>* getWallsList();

        const unsigned getId() const;
        const float2 getFirstCorner() const;
        const float2 getSecondCorner() const;
        const float len();
        const float getDeltaX();
        const float getDeltaY();
        const float getCosAngle();
        const float getSinAngle();
};

#endif // WALL_H
