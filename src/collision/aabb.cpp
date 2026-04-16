#include "aabb.hpp"
#include <cmath>

namespace Collision {

bool aabb_check(AABB a, Vec2 pos_a, AABB b, Vec2 pos_b) {
    float a_left = pos_a.x - a.width / 2.0f;
    float a_right = pos_a.x + a.width / 2.0f;
    float a_top = pos_a.y - a.height / 2.0f;
    float a_bottom = pos_a.y + a.height / 2.0f;

    float b_left = pos_b.x - b.width / 2.0f;
    float b_right = pos_b.x + b.width / 2.0f;
    float b_top = pos_b.y - b.height / 2.0f;
    float b_bottom = pos_b.y + b.height / 2.0f;

    if (a_right <= b_left || a_left >= b_right)
        return false;
    if (a_bottom <= b_top || a_top >= b_bottom)
        return false;
    return true;
}

void aabb_resolve(AABB a, Body &ba, AABB b, Body &bb) {
    float a_left = ba.position.x - a.width / 2.0f;
    float a_right = ba.position.x + a.width / 2.0f;
    float a_top = ba.position.y - a.height / 2.0f;
    float a_bottom = ba.position.y + a.height / 2.0f;

    float b_left = bb.position.x - b.width / 2.0f;
    float b_right = bb.position.x + b.width / 2.0f;
    float b_top = bb.position.y - b.height / 2.0f;
    float b_bottom = bb.position.y + b.height / 2.0f;

    float overlap_x = std::fminf(a_right, b_right) - std::fmaxf(a_left, b_left);
    float overlap_y = std::fminf(a_bottom, b_bottom) - std::fmaxf(a_top, b_top);

    Vec2 normal;
    if (overlap_x < overlap_y) {
        normal.x = (ba.position.x < bb.position.x) ? 1.0f : -1.0f;
        normal.y = 0.0f;
    } else {
        normal.x = 0.0f;
        normal.y = (ba.position.y < bb.position.y) ? 1.0f : -1.0f;
    }

    float correction = (overlap_x < overlap_y ? overlap_x : overlap_y) / 2.0f;
    ba.position.x -= correction * normal.x;
    ba.position.y -= correction * normal.y;
    bb.position.x += correction * normal.x;
    bb.position.y += correction * normal.y;

    float dot =
        (ba.velocity.x - bb.velocity.x) * normal.x + (ba.velocity.y - bb.velocity.y) * normal.y;

    if (dot < 0.0f)
        return;

    float impulse = -2.0f * dot / (1.0f / ba.mass + 1.0f / bb.mass);
    ba.velocity.x += (impulse / ba.mass) * normal.x;
    ba.velocity.y += (impulse / ba.mass) * normal.y;
    bb.velocity.x -= (impulse / bb.mass) * normal.x;
    bb.velocity.y -= (impulse / bb.mass) * normal.y;
}

} // namespace Collision
