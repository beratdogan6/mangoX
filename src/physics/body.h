#ifndef BODY_H
#define BODY_H

#include "../math/vec2.h"

typedef struct {
    Vec2 position;
    Vec2 velocity;
    float rotation;
    float angular_velocity;
    float mass;
} Body;

Body body_create(Vec2 position, float mass);
Body body_update(Body b, float dt);

#endif // !BODY_H
