#ifndef BODY_H
#define BODY_H

#include "../math/vec2.h"

typedef struct {
    Vec2 position;
    Vec2 velocity;
    Vec2 force;
    float rotation;
    float angular_velocity;
    float mass;
} Body;

Body body_create(Vec2 position, float mass);
Body body_update(Body b, float dt);
Body body_add_force(Body b, Vec2 f);

#endif // !BODY_H
