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
    a.velocity = (Vec2){200.0f, 0};

    Body b = body_create((Vec2){screen_width - 100, screen_height / 2}, 1.0f);
    b.radius = BALL_RADIUS;
    b.velocity = (Vec2){-200.0f, 0};

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        a = body_update(a, dt);
        b = body_update(b, dt);

        bool hit = circle_intersects(a, b);
        if (hit)
            circle_resolve(&a, &b);
        Color color_a = hit ? RED : BLUE;
        Color color_b = hit ? RED : GREEN;

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
