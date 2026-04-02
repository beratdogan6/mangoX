#include "body.h"

Body body_create(Vec2 position, float mass) {
    Body b;
    b.position = position;
    b.mass = mass;
    b.velocity = (Vec2){0, 0};
    b.force = (Vec2){0, 0};
    b.angular_velocity = 0.0;
    b.rotation = 0.0;
    b.radius = 0.0;

    return b;
}

Body body_update(Body b, float dt) {
    Vec2 acceleration = vec2_scale(b.force, 1.0 / b.mass);
    b.velocity = vec2_add(b.velocity, vec2_scale(acceleration, dt));
    b.position = vec2_add(b.position, vec2_scale(b.velocity, dt));
    b.force = (Vec2){0, 0};
    return b;
}

Body body_add_force(Body b, Vec2 f) {
    b.force = vec2_add(b.force, f);
    return b;
}
