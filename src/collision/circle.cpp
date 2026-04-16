#include "circle.hpp"

namespace Collision {

bool circle_intersects(Body &a, Body &b) {
    Vec2 sub = a.position - b.position;
    if (sub.len() < a.radius + b.radius)
        return true;
    return false;
}

void circle_resolve(Body &a, Body &b) {
    Vec2 normal = (a.position - b.position).norm();
    float dot = (a.velocity - b.velocity).dot(normal);

    if (dot > 0.0f)
        return;

    float impulse = -2.0f * dot / (1.0f / a.mass + 1.0f / b.mass);

    Vec2 deltaA = normal * (impulse / a.mass);
    Vec2 deltaB = normal * (impulse / b.mass);

    a.velocity = a.velocity + deltaA;
    b.velocity = b.velocity + deltaB;
}

} // namespace Collision
