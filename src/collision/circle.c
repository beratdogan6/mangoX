#include "circle.h"
#include <stdbool.h>

bool circle_intersects(Body circleA, Body circleB) {
    Vec2 sub = vec2_sub(circleA.position, circleB.position);
    if (vec2_len(sub) < (circleA.radius + circleB.radius))
        return true;
    return false;
}

void circle_resolve(Body *circleA, Body *circleB) {
    Vec2 normal = vec2_norm(vec2_sub(circleA->position, circleB->position));
    float dot = vec2_dot(vec2_sub(circleA->velocity, circleB->velocity), normal);
    if (dot > 0.0f)
        return;
    float impulse = -2.0f * dot / (1.0f / circleA->mass + 1.0f / circleB->mass);

    Vec2 deltaA = vec2_scale(normal, impulse / circleA->mass);
    Vec2 deltaB = vec2_scale(normal, impulse / circleB->mass);

    circleA->velocity = vec2_add(circleA->velocity, deltaA);
    circleB->velocity = vec2_sub(circleB->velocity, deltaB);
}
