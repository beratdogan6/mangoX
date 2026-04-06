#ifndef SAT_H
#define SAT_H

#include "../math/vec2.h"
#include "../physics/body.h"

#define SAT_MAX_VERTS 8

typedef struct {
    Vec2 verts[SAT_MAX_VERTS];
    int count;
} Polygon;

Polygon polygon_make_rect(float w, float h);
Polygon polygon_make_triangle(float size);
Polygon polygon_make_regular(int sides, float size);

int sat_check(Polygon a, Vec2 pos_a, Polygon b, Vec2 pos_b);
void sat_resolve(Polygon a, Body *ba, Polygon b, Body *bb);

#endif // !SAT_H
