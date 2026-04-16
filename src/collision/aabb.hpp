#ifndef AABB_HPP
#define AABB_HPP

#include "../math/vec2.hpp"
#include "../physics/body.hpp"

struct AABB {
    float width, height;
    AABB(float width, float height) : width(width), height(height) {}
};

namespace Collision {
bool aabb_check(AABB a, Vec2 pos_a, AABB b, Vec2 pos_b);
void aabb_resolve(AABB a, Body &ba, AABB b, Body &bb);
} // namespace Collision

#endif // !AABB_HPP
