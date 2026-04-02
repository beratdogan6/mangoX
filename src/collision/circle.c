#include "circle.h"
#include <stdbool.h>

bool circle_intersects(Body circleA, Body circleB) {
    Vec2 sub = vec2_sub(circleA.position, circleB.position);
    if (vec2_len(sub) < (circleA.radius + circleB.radius))
        return true;
    return false;
}
