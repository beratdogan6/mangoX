# mangoX

A 2D physics engine written in C from scratch, as a hobby and learning project.

The goal is to implement as much physics and math as possible by hand — no physics libraries, only [raylib](https://www.raylib.com/) for rendering.

## Features

- [x] Vec2 math (add, sub, scale, dot, length, normalize)
- [x] Rigid body (position, velocity, rotation, angular velocity, mass)
- [x] Euler integration
- [x] Force accumulation
- [x] Collision detection — circle, AABB, SAT (convex polygons)
- [x] Collision resolution — impulse-based

## Build

Requires raylib built from source (already included at `raylib-src/`).

```bash
make        # build
make run    # build and run
make clean  # remove build artifacts
```

## Dependencies

- gcc
- raylib (built from source, no system install needed)
- clang-format (optional, for formatting)
