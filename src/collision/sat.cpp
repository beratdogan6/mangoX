#include "sat.hpp"
#include <cfloat>
#include <cmath>

namespace Collision {

Polygon polygon_make_rect(float w, float h) {
    Vec2 verts[4] = {Vec2(-w / 2.0f, -h / 2.0f), Vec2(w / 2.0f, -h / 2.0f),
                     Vec2(w / 2.0f, h / 2.0f), Vec2(-w / 2.0f, h / 2.0f)};
    return Polygon(verts, 4);
}

Polygon polygon_make_triangle(float size) {
    Vec2 verts[3] = {Vec2(0.0f, -size), Vec2(size * 0.866f, size * 0.5f),
                     Vec2(-size * 0.866f, size * 0.5f)};
    return Polygon(verts, 3);
}

Polygon polygon_make_regular(int sides, float size) {
    Vec2 verts[SAT_MAX_VERTS];
    for (int i = 0; i < sides; i++) {
        float angle = (2.0f * M_PI * i) / sides - M_PI / 2.0f;
        verts[i] = Vec2(cosf(angle) * size, sinf(angle) * size);
    }
    return Polygon(verts, sides);
}

static void project(const Polygon &poly, Vec2 pos, Vec2 axis, float &out_min, float &out_max) {
    out_min = FLT_MAX;
    out_max = -FLT_MAX;
    for (int i = 0; i < poly.count; i++) {
        float p = (poly.verts[i] + pos).dot(axis);
        if (p < out_min)
            out_min = p;
        if (p > out_max)
            out_max = p;
    }
}

static bool test_axes(const Polygon &a, Vec2 pos_a, const Polygon &b, Vec2 pos_b,
                      float &min_overlap, Vec2 &min_axis) {
    for (int i = 0; i < a.count; i++) {
        int j = (i + 1) % a.count;
        Vec2 edge = a.verts[j] - a.verts[i];
        Vec2 axis = Vec2(-edge.y, edge.x).norm();

        float a_min, a_max, b_min, b_max;
        project(a, pos_a, axis, a_min, a_max);
        project(b, pos_b, axis, b_min, b_max);

        float overlap = std::fminf(a_max, b_max) - std::fmaxf(a_min, b_min);
        if (overlap <= 0.0f)
            return false;

        if (overlap < min_overlap) {
            min_overlap = overlap;
            min_axis = axis;
        }
    }
    return true;
}

bool sat_check(Polygon a, Vec2 pos_a, Polygon b, Vec2 pos_b) {
    float dummy_overlap = FLT_MAX;
    Vec2 dummy_axis;
    return test_axes(a, pos_a, b, pos_b, dummy_overlap, dummy_axis) &&
           test_axes(b, pos_b, a, pos_a, dummy_overlap, dummy_axis);
}

void sat_resolve(Polygon a, Body &ba, Polygon b, Body &bb) {
    float min_overlap = FLT_MAX;
    Vec2 min_axis;

    if (!test_axes(a, ba.position, b, bb.position, min_overlap, min_axis))
        return;
    if (!test_axes(b, bb.position, a, ba.position, min_overlap, min_axis))
        return;

    Vec2 d = ba.position - bb.position;
    if (d.dot(min_axis) < 0.0f)
        min_axis = min_axis * -1.0f;

    float correction = min_overlap / 2.0f;
    ba.position = ba.position + min_axis * correction;
    bb.position = bb.position - min_axis * correction;

    float dot = (ba.velocity - bb.velocity).dot(min_axis);
    if (dot > 0.0f)
        return;

    float impulse = -2.0f * dot / (1.0f / ba.mass + 1.0f / bb.mass);
    ba.velocity = ba.velocity + min_axis * (impulse / ba.mass);
    bb.velocity = bb.velocity - min_axis * (impulse / bb.mass);
}

} // namespace Collision
