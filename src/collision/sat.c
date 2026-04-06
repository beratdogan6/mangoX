#include "sat.h"
#include <float.h>
#include <math.h>

Polygon polygon_make_rect(float w, float h) {
    Polygon p;
    p.count = 4;
    p.verts[0] = (Vec2){-w / 2.0f, -h / 2.0f};
    p.verts[1] = (Vec2){w / 2.0f, -h / 2.0f};
    p.verts[2] = (Vec2){w / 2.0f, h / 2.0f};
    p.verts[3] = (Vec2){-w / 2.0f, h / 2.0f};
    return p;
}

Polygon polygon_make_triangle(float size) {
    Polygon p;
    p.count = 3;
    p.verts[0] = (Vec2){0.0f, -size};
    p.verts[1] = (Vec2){size * 0.866f, size * 0.5f};
    p.verts[2] = (Vec2){-size * 0.866f, size * 0.5f};
    return p;
}

Polygon polygon_make_regular(int sides, float size) {
    Polygon p;
    p.count = sides;
    for (int i = 0; i < sides; i++) {
        float angle = (2.0f * (float)M_PI * i) / sides - (float)M_PI / 2.0f;
        p.verts[i].x = cosf(angle) * size;
        p.verts[i].y = sinf(angle) * size;
    }
    return p;
}

static void project(Polygon poly, Vec2 pos, Vec2 axis, float *out_min, float *out_max) {
    float mn = FLT_MAX, mx = -FLT_MAX;
    for (int i = 0; i < poly.count; i++) {
        float p = vec2_dot((Vec2){poly.verts[i].x + pos.x, poly.verts[i].y + pos.y}, axis);
        if (p < mn)
            mn = p;
        if (p > mx)
            mx = p;
    }
    *out_min = mn;
    *out_max = mx;
}

static int test_axes(Polygon a, Vec2 pos_a, Polygon b, Vec2 pos_b, float *min_overlap,
                     Vec2 *min_axis) {
    for (int i = 0; i < a.count; i++) {
        int j = (i + 1) % a.count;
        Vec2 edge = vec2_sub(a.verts[j], a.verts[i]);
        Vec2 axis = vec2_norm((Vec2){-edge.y, edge.x});

        float a_min, a_max, b_min, b_max;
        project(a, pos_a, axis, &a_min, &a_max);
        project(b, pos_b, axis, &b_min, &b_max);

        float overlap = fminf(a_max, b_max) - fmaxf(a_min, b_min);
        if (overlap <= 0.0f)
            return 0;

        if (overlap < *min_overlap) {
            *min_overlap = overlap;
            *min_axis = axis;
        }
    }
    return 1;
}

int sat_check(Polygon a, Vec2 pos_a, Polygon b, Vec2 pos_b) {
    float dummy_overlap = FLT_MAX;
    Vec2 dummy_axis = {0};
    return test_axes(a, pos_a, b, pos_b, &dummy_overlap, &dummy_axis) &&
           test_axes(b, pos_b, a, pos_a, &dummy_overlap, &dummy_axis);
}

void sat_resolve(Polygon a, Body *ba, Polygon b, Body *bb) {
    float min_overlap = FLT_MAX;
    Vec2 min_axis = {0};

    if (!test_axes(a, ba->position, b, bb->position, &min_overlap, &min_axis))
        return;
    if (!test_axes(b, bb->position, a, ba->position, &min_overlap, &min_axis))
        return;

    // ensure normal points from b toward a
    Vec2 d = vec2_sub(ba->position, bb->position);
    if (vec2_dot(d, min_axis) < 0.0f)
        min_axis = vec2_scale(min_axis, -1.0f);

    // position correction
    float correction = min_overlap / 2.0f;
    ba->position.x += correction * min_axis.x;
    ba->position.y += correction * min_axis.y;
    bb->position.x -= correction * min_axis.x;
    bb->position.y -= correction * min_axis.y;

    // impulse
    float dot = vec2_dot(vec2_sub(ba->velocity, bb->velocity), min_axis);
    if (dot > 0.0f)
        return;

    float impulse = -2.0f * dot / (1.0f / ba->mass + 1.0f / bb->mass);
    ba->velocity.x += (impulse / ba->mass) * min_axis.x;
    ba->velocity.y += (impulse / ba->mass) * min_axis.y;
    bb->velocity.x -= (impulse / bb->mass) * min_axis.x;
    bb->velocity.y -= (impulse / bb->mass) * min_axis.y;
}
