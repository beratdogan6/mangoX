# mangoX — Roadmap

## Phase 1: 2D Physics Engine in C (COMPLETED)

- [x] Math primitives (Vec2)
- [x] Rigid body + Euler integration
- [x] Force accumulation
- [x] Collision detection — AABB, circle, SAT
- [x] Impulse-based collision resolution

---

## Phase 2: Rewrite in C++ with OpenGL + ECS

The goal of this phase is threefold:

- Learn OpenGL by re-implementing what raylib was doing under the hood
- Migrate the codebase from C to C++
- Redesign the architecture around ECS (Entity-Component-System)

The physics knowledge from Phase 1 carries over directly — we already understand
the math. Rendering the same 2D simulation without raylib will make OpenGL errors
easy to isolate because we know exactly what correct output looks like.

### 2a — OpenGL Fundamentals

- [x] Window + OpenGL context setup (GLFW, no raylib)
- [x] Shader pipeline: write first vertex + fragment shader
- [x] VAO / VBO — upload polygon geometry to the GPU
- [ ] Draw the Phase 1 polygon demo using raw OpenGL
- [ ] Basic camera / projection matrix (orthographic for 2D)
- [ ] Debug utilities: FPS counter, draw call stats

### 2b — C++ Migration

- [x] Port math primitives (Vec2, later Vec3) to C++ — keep it plain structs, no classes
- [x] Port Body, collision detection, SAT to C++
- [x] Use RAII where it makes sense (buffers, shader programs, window)
- [x] Avoid deep inheritance hierarchies — prefer composition

### 2c — ECS Architecture

- [ ] Define Component types: Transform, RigidBody, Collider, Renderable
- [ ] Implement a simple component storage (struct-of-arrays, not array-of-structs)
- [ ] Systems: PhysicsSystem, CollisionSystem, RenderSystem
- [ ] Re-implement the Phase 1 demo on top of ECS — same behavior, new architecture

---

## Phase 2 — Current Status (June 2026)

C++ migration and basic OpenGL renderer are done:

- [x] Window + GLFW + GLAD setup
- [x] Vertex/fragment shader pipeline
- [x] VAO/VBO, colored triangle rendering
- [x] Vec2, Body, Circle, AABB, SAT ported to C++

ECS architecture is not started yet — may revisit later.
Phase 3 started on branch `feat/mat4`: Vec3, Mat4, Quat done; 3D rigid body next.

---

## Phase 3: 3D

### Next steps in order

1. **Vec3** — extend Vec2 to 3D, add cross product ← done
2. **Mat4** — 4x4 matrix, needed for transform/view/projection ← done
   - **Quat** — orientation primitive (w-last, Hamilton product, integrate) ← done
3. **3D Rigid Body** — update Body to use Vec3 + Quat orientation, inverse inertia tensor
4. **Camera** — view + perspective projection matrix
5. **3D Mesh render** — draw a cube, connect to physics
6. **3D Collision** — AABB, sphere, OBB
7. **GJK / EPA** — convex collision in 3D
8. **3D impulse resolution**

---

## Notes

- ECS over OOP: game/physics engines benefit from data-oriented design.
  Components are plain data, systems hold the logic. No virtual dispatch, cache-friendly.
- C++ is used for RAII, templates, and std:: — not for deep class hierarchies.
- OpenGL target version: 3.3 Core Profile.
- Windowing: GLFW (lightweight, no extra abstractions).
