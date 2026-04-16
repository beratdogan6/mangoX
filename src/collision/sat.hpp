#ifndef SAT_HPP
#define SAT_HPP

#include "../math/vec2.hpp"
#include "../physics/body.hpp"

constexpr int SAT_MAX_VERTS = 8;

struct Polygon {
    Vec2 verts[SAT_MAX_VERTS];
    int count;

    Polygon(Vec2 *v, int c) : count(c) {
        for (int i = 0; i < c; i++)
            verts[i] = v[i];
    }
    Polygon() : count(0) {}
};

namespace Collision {
Polygon polygon_make_rect(float w, float h);
Polygon polygon_make_triangle(float size);
Polygon polygon_make_regular(int sides, float size);

bool sat_check(Polygon a, Vec2 pos_a, Polygon b, Vec2 pos_b);
void sat_resolve(Polygon a, Body &ba, Polygon b, Body &bb);
} // namespace Collision

#endif // !SAT_HPP
