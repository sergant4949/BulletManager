#ifndef FLOAT2_H
#define FLOAT2_H

#include <iostream>

class float2 {
    public:
        float x;
        float y;

        float2(float x = 0, float y = 0);
        float distance(const float2& other);
        bool operator==(const float2& other);
        bool operator!=(const float2& other);
};

#endif // FLOAT2_H
