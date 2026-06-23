// =============================================================================
// mat4.hpp — 4x4 floating-point matrix
//
// The transform workhorse: model/view/projection, camera math, and (later) the
// world-space inertia tensor. Conventions are fixed here and must never be
// violated elsewhere:
//
//   - Storage:        COLUMN-MAJOR. m[16] is 4 contiguous columns. This matches
//                     GLSL's mat4 and lets us upload with glUniformMatrix4fv(..,
//                     GL_FALSE, ..) directly — no transpose on the hot path.
//   - Indexing:       element at (row r, col c) lives at m[c * 4 + r].
//                     Use operator()(r, c) so call sites never hardcode that.
//   - Multiplication: column-vector convention. Transforms compose right-to-left
//                     (MVP = P * V * M) and apply as clip = MVP * v.
//   - Handedness:     right-handed, matching Vec3 (forward = -Z). Projection maps
//                     into OpenGL clip space with NDC z in [-1, 1].
//
// There is intentionally no Vec4: homogeneous transforms are exposed as
// transformPoint (implicit w = 1, perspective divide) and transformDirection
// (w = 0, ignores translation). Add Vec4 only when something genuinely needs it.

#ifndef MAT4_HPP
#define MAT4_HPP

#include "vec3.hpp"

#include <cmath>

struct Mat4 {
    // Column-major: m[col * 4 + row].
    float m[16];

    // Default-constructs to the zero matrix; use Mat4::identity() for I.
    constexpr Mat4() : m{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f} {}

    // (row, col) accessor — the only place the storage layout is encoded.
    float &operator()(int r, int c) { return m[c * 4 + r]; }
    float operator()(int r, int c) const { return m[c * 4 + r]; }

    static constexpr Mat4 identity() {
        Mat4 r;
        r.m[0] = 1.0f;
        r.m[5] = 1.0f;
        r.m[10] = 1.0f;
        r.m[15] = 1.0f;
        return r;
    }

    // --- Affine builders ------------------------------------------------------

    static Mat4 translate(const Vec3 &t) {
        Mat4 r = identity();
        r.m[12] = t.x;
        r.m[13] = t.y;
        r.m[14] = t.z;
        return r;
    }

    static Mat4 scale(const Vec3 &s) {
        Mat4 r;
        r.m[0] = s.x;
        r.m[5] = s.y;
        r.m[10] = s.z;
        r.m[15] = 1.0f;
        return r;
    }

    // Right-handed rotation of `angle` radians about `axis` (Rodrigues' formula).
    // `axis` is normalized internally; a degenerate (near-zero) axis yields I.
    static Mat4 rotate(const Vec3 &axis, float angle) {
        Vec3 a = axis.norm();
        if (a.lenSq() == 0.0f)
            return identity();

        float c = cosf(angle);
        float s = sinf(angle);
        float t = 1.0f - c;
        float x = a.x, y = a.y, z = a.z;

        Mat4 r;
        r(0, 0) = t * x * x + c;
        r(0, 1) = t * x * y - s * z;
        r(0, 2) = t * x * z + s * y;
        r(1, 0) = t * x * y + s * z;
        r(1, 1) = t * y * y + c;
        r(1, 2) = t * y * z - s * x;
        r(2, 0) = t * x * z - s * y;
        r(2, 1) = t * y * z + s * x;
        r(2, 2) = t * z * z + c;
        r(3, 3) = 1.0f;
        return r;
    }

    // --- Camera / projection --------------------------------------------------

    // Right-handed view matrix. Looks from `eye` toward `target`, `up` need not
    // be orthogonal to the view direction (it is re-orthogonalized).
    static Mat4 lookAt(const Vec3 &eye, const Vec3 &target, const Vec3 &up) {
        Vec3 f = (target - eye).norm(); // forward (into the scene)
        Vec3 s = cross(f, up).norm();   // right
        Vec3 u = cross(s, f);           // recomputed up (already unit)

        Mat4 r = identity();
        r(0, 0) = s.x;
        r(0, 1) = s.y;
        r(0, 2) = s.z;
        r(1, 0) = u.x;
        r(1, 1) = u.y;
        r(1, 2) = u.z;
        r(2, 0) = -f.x;
        r(2, 1) = -f.y;
        r(2, 2) = -f.z;
        r(0, 3) = -dot(s, eye);
        r(1, 3) = -dot(u, eye);
        r(2, 3) = dot(f, eye);
        return r;
    }

    // Right-handed perspective into OpenGL clip space (NDC z in [-1, 1]).
    // fovY in radians, aspect = width / height, 0 < near < far.
    static Mat4 perspective(float fovY, float aspect, float near, float far) {
        float f = 1.0f / tanf(fovY * 0.5f);
        Mat4 r; // zero matrix
        r(0, 0) = f / aspect;
        r(1, 1) = f;
        r(2, 2) = (far + near) / (near - far);
        r(2, 3) = (2.0f * far * near) / (near - far);
        r(3, 2) = -1.0f;
        return r;
    }

    Mat4 transposed() const {
        Mat4 r;
        for (int c = 0; c < 4; ++c)
            for (int rr = 0; rr < 4; ++rr)
                r(rr, c) = (*this)(c, rr);
        return r;
    }

    // Transform a position: implicit w = 1, with perspective divide so this is
    // correct for projective matrices too. Guards a near-zero w.
    Vec3 transformPoint(const Vec3 &v) const {
        const Mat4 &a = *this;
        float x = a(0, 0) * v.x + a(0, 1) * v.y + a(0, 2) * v.z + a(0, 3);
        float y = a(1, 0) * v.x + a(1, 1) * v.y + a(1, 2) * v.z + a(1, 3);
        float z = a(2, 0) * v.x + a(2, 1) * v.y + a(2, 2) * v.z + a(2, 3);
        float w = a(3, 0) * v.x + a(3, 1) * v.y + a(3, 2) * v.z + a(3, 3);
        if (fabsf(w) > 1e-8f && w != 1.0f) {
            float inv = 1.0f / w;
            return Vec3(x * inv, y * inv, z * inv);
        }
        return Vec3(x, y, z);
    }

    // Transform a direction: w = 0, so translation is ignored. Not normalized;
    // not valid under non-uniform scale (use the inverse-transpose for normals).
    Vec3 transformDirection(const Vec3 &v) const {
        const Mat4 &a = *this;
        return Vec3(a(0, 0) * v.x + a(0, 1) * v.y + a(0, 2) * v.z,
                    a(1, 0) * v.x + a(1, 1) * v.y + a(1, 2) * v.z,
                    a(2, 0) * v.x + a(2, 1) * v.y + a(2, 2) * v.z);
    }
};

// Matrix product: (A * B)(i, j) = sum_k A(i, k) * B(k, j).
inline Mat4 operator*(const Mat4 &a, const Mat4 &b) {
    Mat4 r;
    for (int c = 0; c < 4; ++c) {
        for (int row = 0; row < 4; ++row) {
            float sum = 0.0f;
            for (int k = 0; k < 4; ++k)
                sum += a(row, k) * b(k, c);
            r(row, c) = sum;
        }
    }
    return r;
}

#endif // !MAT4_HPP
