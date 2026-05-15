// =============================================================================
// vec3.hpp — 3-component floating-point vector
//
// Core math primitive for all 3D operations: physics simulation, collision
// detection, rendering transforms, and camera math. Every system in the engine
// touches this type — keep it tight, keep it fast.

#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>

struct Vec3 {
    float x, y, z;

    constexpr Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    constexpr Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

    float len() const { return sqrtf(x * x + y * y + z * z); }
    float lenSq() const { return x * x + y * y + z * z; }

    Vec3 norm() const {
        float l = len();
        return l > 0.0f ? Vec3(x / l, y / l, z / l) : Vec3(0.0f, 0.0f, 0.0f);
    }

    Vec3 &operator+=(const Vec3 &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    Vec3 &operator-=(const Vec3 &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    Vec3 &operator*=(float s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }
    Vec3 &operator/=(float s) {
        float inv = 1.0f / s;
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }
    static constexpr Vec3 zero() { return Vec3(0.0f, 0.0f, 0.0f); }
    static constexpr Vec3 one() { return Vec3(1.0f, 1.0f, 1.0f); }
    static constexpr Vec3 up() { return Vec3(0.0f, 1.0f, 0.0f); }
    static constexpr Vec3 down() { return Vec3(0.0f, -1.0f, 0.0f); }
    static constexpr Vec3 left() { return Vec3(-1.0f, 0.0f, 0.0f); }
    static constexpr Vec3 right() { return Vec3(1.0f, 0.0f, 0.0f); }
    static constexpr Vec3 forward() { return Vec3(0.0f, 0.0f, -1.0f); }
    static constexpr Vec3 back() { return Vec3(0.0f, 0.0f, 1.0f); }
};

inline Vec3 operator+(Vec3 a, Vec3 b) { return Vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vec3 operator-(Vec3 a, Vec3 b) { return Vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vec3 operator-(Vec3 a) { return Vec3(-a.x, -a.y, -a.z); }
inline Vec3 operator*(Vec3 a, float s) { return Vec3(a.x * s, a.y * s, a.z * s); }
inline Vec3 operator*(float s, Vec3 a) { return Vec3(a.x * s, a.y * s, a.z * s); }
inline Vec3 operator/(Vec3 a, float s) { return a * (1.0f / s); }

inline float dot(Vec3 a, Vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline Vec3 cross(Vec3 a, Vec3 b) {
    return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
inline bool approxEq(Vec3 a, Vec3 b, float eps = 1e-5f) {
    return fabsf(a.x - b.x) < eps && fabsf(a.y - b.y) < eps && fabsf(a.z - b.z) < eps;
}
inline float distanceSq(Vec3 a, Vec3 b) { return (a - b).lenSq(); }
inline float distance(Vec3 a, Vec3 b) { return sqrtf(distanceSq(a, b)); }
inline Vec3 lerp(Vec3 a, Vec3 b, float t) { return a + (b - a) * t; }
inline Vec3 reflect(const Vec3 &v, const Vec3 &n) { return v - 2.0f * dot(v, n) * n; }

#endif // !VEC3_HPP
