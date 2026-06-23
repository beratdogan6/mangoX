// =============================================================================
// quat.hpp — unit quaternion for 3D orientation
//
// Orientation state for rigid bodies. We store orientation as a quaternion (never
// Euler angles): no gimbal lock, cheap composition, stable interpolation, and a
// trivial re-normalization to fight drift. Convert to a matrix only for rendering.
//
// Conventions (fixed here, never violated elsewhere):
//   - Layout:       (x, y, z, w), w-LAST. Matches Bullet's btQuaternion and GLM's
//                   memory order. Identity = (0, 0, 0, 1).
//   - Product:      Hamilton product. `a * b` is "apply b, then a" — the same
//                   right-to-left composition order as matrices.
//   - Rotation:     a vector is rotated by q as q * v * q^-1 (right-handed),
//                   matching Vec3 (forward = -Z) and Mat4.
//   - Unit-ness:    rotation assumes a UNIT quaternion. Re-normalize periodically
//                   to counter integration drift.

#ifndef QUAT_HPP
#define QUAT_HPP

#include "mat4.hpp"
#include "vec3.hpp"

#include <cmath>

struct Quat {
    float x, y, z, w;

    constexpr Quat() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
    constexpr Quat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    static constexpr Quat identity() { return Quat(0.0f, 0.0f, 0.0f, 1.0f); }

    // Unit quaternion for a right-handed rotation of `angle` radians about `axis`.
    // `axis` is normalized internally; a degenerate (near-zero) axis yields identity.
    static Quat fromAxisAngle(const Vec3 &axis, float angle) {
        Vec3 a = axis.norm();
        if (a.lenSq() == 0.0f)
            return identity();
        float half = angle * 0.5f;
        float s = sinf(half);
        return Quat(a.x * s, a.y * s, a.z * s, cosf(half));
    }

    float lenSq() const { return x * x + y * y + z * z + w * w; }
    float len() const { return sqrtf(lenSq()); }

    // Re-normalize to unit length; falls back to identity on a degenerate quat.
    Quat normalized() const {
        float l = len();
        if (l <= 0.0f)
            return identity();
        float inv = 1.0f / l;
        return Quat(x * inv, y * inv, z * inv, w * inv);
    }

    // For a unit quaternion, conjugate == inverse (and is far cheaper).
    Quat conjugate() const { return Quat(-x, -y, -z, w); }

    // General inverse (valid for non-unit quats); guards a near-zero norm.
    Quat inverse() const {
        float n = lenSq();
        if (n <= 0.0f)
            return identity();
        float inv = 1.0f / n;
        return Quat(-x * inv, -y * inv, -z * inv, w * inv);
    }

    // Rotate a vector: v' = q * v * q^-1, in the optimized form that avoids
    // building a matrix. Assumes *this is unit-length.
    Vec3 rotate(const Vec3 &v) const {
        Vec3 u(x, y, z);
        Vec3 t = 2.0f * cross(u, v);
        return v + w * t + cross(u, t);
    }

    // Rotation matrix for rendering (column-major via Mat4's accessor).
    // Assumes a unit quaternion.
    Mat4 toMat4() const {
        float xx = x * x, yy = y * y, zz = z * z;
        float xy = x * y, xz = x * z, yz = y * z;
        float wx = w * x, wy = w * y, wz = w * z;

        Mat4 r = Mat4::identity();
        r(0, 0) = 1.0f - 2.0f * (yy + zz);
        r(0, 1) = 2.0f * (xy - wz);
        r(0, 2) = 2.0f * (xz + wy);
        r(1, 0) = 2.0f * (xy + wz);
        r(1, 1) = 1.0f - 2.0f * (xx + zz);
        r(1, 2) = 2.0f * (yz - wx);
        r(2, 0) = 2.0f * (xz - wy);
        r(2, 1) = 2.0f * (yz + wx);
        r(2, 2) = 1.0f - 2.0f * (xx + yy);
        return r;
    }

    // Integrate this orientation by world-space angular velocity `omega` (rad/s)
    // over `dt`, using dq/dt = 0.5 * omega_quat * q with omega_quat = (omega, 0).
    // First-order; returns a re-normalized result. Defined out-of-line below so
    // the Hamilton-product operator is visible.
    Quat integrate(const Vec3 &omega, float dt) const;
};

// Hamilton product: (a * b) applies b first, then a.
inline Quat operator*(const Quat &a, const Quat &b) {
    return Quat(a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
                a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
                a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
                a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z);
}

inline Quat operator*(const Quat &q, float s) {
    return Quat(q.x * s, q.y * s, q.z * s, q.w * s);
}
inline Quat operator+(const Quat &a, const Quat &b) {
    return Quat(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

inline float dot(const Quat &a, const Quat &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline Quat Quat::integrate(const Vec3 &omega, float dt) const {
    Quat wq(omega.x, omega.y, omega.z, 0.0f);
    Quat dq = wq * (*this);
    return (*this + dq * (0.5f * dt)).normalized();
}

#endif // !QUAT_HPP
