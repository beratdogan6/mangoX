#include "vec2.h"
#include <math.h>

Vec2 vec2_add(Vec2 a, Vec2 b) { return (Vec2){a.x + b.x, a.y + b.y}; }
Vec2 vec2_sub(Vec2 a, Vec2 b) { return (Vec2){a.x - b.x, a.y - b.y}; }
Vec2 vec2_scale(Vec2 a, float s) { return (Vec2){a.x * s, a.y * s}; }
float vec2_dot(Vec2 a, Vec2 b) { return a.x * b.x + a.y * b.y; }
float vec2_len(Vec2 a) { return sqrtf(a.x * a.x + a.y * a.y); }
Vec2 vec2_norm(Vec2 a) {
    float l = vec2_len(a);
    return l > 0 ? vec2_scale(a, 1.0f / l) : (Vec2){0, 0};
}
