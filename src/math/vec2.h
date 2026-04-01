#ifndef VEC2_H
#define VEC2_H

typedef struct {
    float x, y;
} Vec2;

Vec2 vec2_add(Vec2 a, Vec2 b);
Vec2 vec2_sub(Vec2 a, Vec2 b);
Vec2 vec2_scale(Vec2 a, float s);
float vec2_dot(Vec2 a, Vec2 b);
float vec2_len(Vec2 a);
Vec2 vec2_norm(Vec2 a);

#endif
