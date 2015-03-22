#include "float2.h"
#include <cmath>

float2::float2(float x, float y) : x(x), y(y) {}

float float2::distance(const float2& other) {
    return hypot(this->x - other.x, this->y - other.y);
}

bool float2::operator==(const float2& other) {
    return this->x == other.x && this->y == other.y;
}

bool float2::operator!=(const float2& other) {
    return !operator==(other);
}
