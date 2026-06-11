// =============================================================================
// vec4.hpp — 4-component floating-point vector
//
// Unlike Vec3, this is not a general geometric type. It exists for two jobs:
// homogeneous coordinates (Mat4 * Vec4 — w=1 for points, w=0 for directions)
// and RGBA colors. Deliberately minimal: no cross, no length, no direction
// constants — those concepts don't apply here.

#ifndef VEC4_HPP
#define VEC4_HPP

#include <cmath>

#include "vec3.hpp"

struct Vec4 {
    float x, y, z, w;

    constexpr Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    constexpr Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    // w=1: point (affected by translation), w=0: direction (not affected)
    constexpr Vec4(const Vec3 &v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}

    // Drop w — used after perspective divide or to extract a Vec3 result
    constexpr Vec3 xyz() const { return Vec3(x, y, z); }

    Vec4 &operator+=(const Vec4 &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }
    Vec4 &operator-=(const Vec4 &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }
    Vec4 &operator*=(float s) {
        x *= s;
        y *= s;
        z *= s;
        w *= s;
        return *this;
    }
    Vec4 &operator/=(float s) {
        float inv = 1.0f / s;
        x *= inv;
        y *= inv;
        z *= inv;
        w *= inv;
        return *this;
    }
    static constexpr Vec4 zero() { return Vec4(0.0f, 0.0f, 0.0f, 0.0f); }
    static constexpr Vec4 one() { return Vec4(1.0f, 1.0f, 1.0f, 1.0f); }
};

inline Vec4 operator+(Vec4 a, Vec4 b) { return Vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
inline Vec4 operator-(Vec4 a, Vec4 b) { return Vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
inline Vec4 operator-(Vec4 a) { return Vec4(-a.x, -a.y, -a.z, -a.w); }
inline Vec4 operator*(Vec4 a, float s) { return Vec4(a.x * s, a.y * s, a.z * s, a.w * s); }
inline Vec4 operator*(float s, Vec4 a) { return Vec4(a.x * s, a.y * s, a.z * s, a.w * s); }
inline Vec4 operator/(Vec4 a, float s) { return a * (1.0f / s); }

// Mat4 * Vec4 is four of these — the core operation this type exists for
inline float dot(Vec4 a, Vec4 b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
inline bool approxEq(Vec4 a, Vec4 b, float eps = 1e-5f) {
    return fabsf(a.x - b.x) < eps && fabsf(a.y - b.y) < eps && fabsf(a.z - b.z) < eps &&
           fabsf(a.w - b.w) < eps;
}

#endif // !VEC4_HPP
