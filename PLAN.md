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
- [ ] Window + OpenGL context setup (GLFW, no raylib)
- [ ] Shader pipeline: write first vertex + fragment shader
- [ ] VAO / VBO — upload polygon geometry to the GPU
- [ ] Draw the Phase 1 polygon demo using raw OpenGL
- [ ] Basic camera / projection matrix (orthographic for 2D)
- [ ] Debug utilities: FPS counter, draw call stats

### 2b — C++ Migration
- [ ] Port math primitives (Vec2, later Vec3) to C++ — keep it plain structs, no classes
- [ ] Port Body, collision detection, SAT to C++
- [ ] Use RAII where it makes sense (buffers, shader programs, window)
- [ ] Avoid deep inheritance hierarchies — prefer composition

### 2c — ECS Architecture
- [ ] Define Component types: Transform, RigidBody, Collider, Renderable
- [ ] Implement a simple component storage (struct-of-arrays, not array-of-structs)
- [ ] Systems: PhysicsSystem, CollisionSystem, RenderSystem
- [ ] Re-implement the Phase 1 demo on top of ECS — same behavior, new architecture

---

## Phase 3: 3D (Future)
- [ ] Extend Vec2 → Vec3, add Mat4
- [ ] Perspective projection
- [ ] 3D collision primitives (AABB, OBB, sphere)
- [ ] GJK / EPA for 3D convex collision
- [ ] 3D impulse resolution

---

## Notes
- ECS over OOP: game/physics engines benefit from data-oriented design.
  Components are plain data, systems hold the logic. No virtual dispatch, cache-friendly.
- C++ is used for RAII, templates, and std:: — not for deep class hierarchies.
- OpenGL target version: 3.3 Core Profile.
- Windowing: GLFW (lightweight, no extra abstractions).
