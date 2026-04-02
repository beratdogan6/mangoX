#include "collision/circle.h"
#include "physics/body.h"
#include "raylib.h"
#include <stdio.h>

#define BALL_RADIUS 20
#define HORIZONTAL_FORCE 2000.0f

int main(void) {
    const int screen_width = 1280;
    const int screen_height = 720;

    InitWindow(screen_width, screen_height, "mangoX - Physics Engine");
    SetTargetFPS(60);

    Body a = body_create((Vec2){100, screen_height / 2}, 1.0f);
    a.radius = BALL_RADIUS;

    Body b = body_create((Vec2){screen_width - 100, screen_height / 2}, 1.0f);
    b.radius = BALL_RADIUS;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        a = body_add_force(a, (Vec2){HORIZONTAL_FORCE, 981.0f * a.mass});
        b = body_add_force(b, (Vec2){-HORIZONTAL_FORCE, 981.0f * b.mass});

        a = body_update(a, dt);
        b = body_update(b, dt);

        bool hit = circle_intersects(a, b);
        Color color_a = hit ? RED : RAYWHITE;
        Color color_b = hit ? RED : RAYWHITE;

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("mangoX", 10, 10, 20, RAYWHITE);

        char debug[128];
        snprintf(debug, sizeof(debug), "FPS: %d\ncollision: %s", GetFPS(), hit ? "YES" : "NO");
        DrawText(debug, screen_width - 160, 10, 18, GREEN);
        DrawCircle((int)a.position.x, (int)a.position.y, BALL_RADIUS, color_a);
        DrawCircle((int)b.position.x, (int)b.position.y, BALL_RADIUS, color_b);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
