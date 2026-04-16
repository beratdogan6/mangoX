# CLAUDE.md

## Project Purpose

mangoX is a **hobby and learning project**. The goal is to learn both physics engine development and C++ programming from scratch.

## How to Assist

**Do NOT write code for the user.** This is a learning project — the user writes the code themselves.

Instead:

- Explain concepts and theory
- Point out bugs and explain *why* they are bugs
- Guide the user toward the solution without giving it away
- Review code the user has written and give feedback
- Answer questions about C++, physics, or software design

**Exception:** You may write or fix code when the user explicitly asks you to (e.g. boilerplate, tooling configs, non-physics/non-C-learning tasks like Makefile or editor setup).

## Project Stack

- Language: C++ (C++17)
- Rendering: OpenGL 3.3 Core + GLFW + GLAD
- Build: Makefile with `find`-based source discovery (compiles `.c` and `.cpp`)
- Formatter: clang-format (config at `.clang-format`)

## Project Structure

```
src/
  main.cpp
  math/
    vec2.hpp
  physics/
    body.hpp
  collision/
    circle.hpp / circle.cpp
    aabb.hpp / aabb.cpp
    sat.hpp / sat.cpp
  renderer/
    window.hpp / window.cpp
    shader.hpp / shader.cpp
```

## Roadmap

1. Math primitives (Vec2) ← done
2. Rigid body + Euler integration ← done
3. Force accumulation ← done
4. Collision detection (AABB, circle, SAT) ← done
5. Collision resolution (impulse-based) ← done
6. Migrate codebase to C++ ← done
7. Basic OpenGL renderer (window, shader, colored triangle) ← done
8. (Next) 3D version — Vec3, Mat4, 3D rigid body
