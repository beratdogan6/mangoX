#include "body.h"

Body body_create(Vec2 position, float mass) {
    Body b;
    b.position = position;
    b.mass = mass;
    b.velocity = (Vec2){0, 0};
    b.angular_velocity = 0.0;
    b.rotation = 0.0;

    return b;
}

Body body_update(Body b, float dt) {
    Vec2 gravity = (Vec2){0, 981.0f};
    b.velocity = vec2_add(b.velocity, vec2_scale(gravity, dt));
    b.position = vec2_add(b.position, vec2_scale(b.velocity, dt));
    return b;
}
