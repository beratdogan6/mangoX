# mangoX

A physics engine written in C++ from scratch, as a hobby and learning project.

The goal is to implement physics and math by hand — no physics libraries. Rendering uses OpenGL 3.3 Core + GLFW + GLAD.

## Features

- [x] Vec2 math (add, sub, scale, dot, length, normalize)
- [x] Rigid body (position, velocity, rotation, angular velocity, mass)
- [x] Euler integration
- [x] Force accumulation
- [x] Collision detection — circle, AABB, SAT (convex polygons)
- [x] Collision resolution — impulse-based
- [x] OpenGL renderer — window, shader, colored triangle
- [ ] Vec3, Mat4
- [ ] 3D rigid body
- [ ] 3D collision detection

## Build

Requires GLFW built from source (included at `glfw-src/`) and GLAD (included at `glad-src/`).

```bash
make        # build
make run    # build and run
make clean  # remove build artifacts
```

## Dependencies

- g++
- GLFW (built from source, no system install needed)
- GLAD (included)
- clang-format (optional, for formatting)
