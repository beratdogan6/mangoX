#ifndef AABB_H
#define AABB_H

#include "../math/vec2.h"
#include "../physics/body.h"

typedef struct {
    float width;
    float height;
} AABB;

int aabb_check(AABB a, Vec2 pos_a, AABB b, Vec2 pos_b);
void aabb_resolve(AABB a, Body *ba, AABB b, Body *bb);

#endif // !AABB_H
