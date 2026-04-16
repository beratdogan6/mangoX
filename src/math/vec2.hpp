#ifndef VEC2_HPP
#define VEC2_HPP

#include <cmath>

struct Vec2 {
    float x, y;

    Vec2(float x, float y) : x(x), y(y) {}
    Vec2() : x(0.0), y(0.0) {}

    Vec2 add(Vec2 other) { return Vec2{x + other.x, y + other.y}; };
    Vec2 sub(Vec2 other) { return Vec2{x - other.x, y - other.y}; };
    Vec2 scale(float s) { return Vec2{x * s, y * s}; }
    float dot(Vec2 other) { return x * other.x + y * other.y; }
    float len() { return sqrtf(x * x + y * y); }
    Vec2 norm() {
        float l = len();
        return l > 0 ? scale(1.0f / l) : Vec2(0, 0);
    }
};

inline Vec2 operator+(Vec2 a, Vec2 b) { return a.add(b); }
inline Vec2 operator-(Vec2 a, Vec2 b) { return a.sub(b); }
inline Vec2 operator*(Vec2 a, float s) { return a.scale(s); }
inline Vec2 operator*(float s, Vec2 a) { return a.scale(s); }

#endif
