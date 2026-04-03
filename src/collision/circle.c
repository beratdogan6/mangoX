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
    float impulse = -2 * vec2_dot(vec2_sub(circleA->velocity, circleB->velocity), normal) /
                    (1 / circleA->mass + 1 / circleB->mass);

    Vec2 deltaA = vec2_scale(normal, impulse / circleA->mass);
    Vec2 deltaB = vec2_scale(normal, impulse / circleB->mass);
    circleA->velocity = vec2_add(circleA->velocity, deltaA);
    circleB->velocity = vec2_sub(circleB->velocity, deltaB);
}
