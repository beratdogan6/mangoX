#ifndef BODY_HPP
#define BODY_HPP

#include "../math/vec2.hpp"

struct Body {
    Vec2 position;
    Vec2 velocity;
    Vec2 force;
    float rotation;
    float angular_velocity;
    float mass;
    float radius;

    Body(Vec2 position, float mass) : position(position), mass(mass) {
        velocity = Vec2(0.0, 0.0);
        force = Vec2(0.0, 0.0);
        rotation = 0.0;
        angular_velocity = 0.0;
        radius = 0.0;
    }

    Body update(float dt) {
        Vec2 acceleration = force * (1.0f / mass);
        velocity = velocity + acceleration * dt;
        position = position + velocity * dt;
        force = Vec2(0.0, 0.0);

        return *this;
    }

    Body add_force(Vec2 f) {
        force = force + f;

        return *this;
    }
};

#endif // !BODY_HPP
