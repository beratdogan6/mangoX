#include "body.h"

Body body_create(Vec2 position, float mass) {
    Body b;
    b.position = position;
    b.mass = mass;
    b.velocity = (Vec2){0.0f, 0.0f};
    b.force = (Vec2){0.0f, 0.0f};
    b.angular_velocity = 0.0f;
    b.rotation = 0.0f;
    b.radius = 0.0f;

    return b;
}

Body body_update(Body b, float dt) {
    Vec2 acceleration = vec2_scale(b.force, 1.0f / b.mass);
    b.velocity = vec2_add(b.velocity, vec2_scale(acceleration, dt));
    b.position = vec2_add(b.position, vec2_scale(b.velocity, dt));
    b.force = (Vec2){0.0f, 0.0f};
    return b;
}

Body body_add_force(Body b, Vec2 f) {
    b.force = vec2_add(b.force, f);
    return b;
}
