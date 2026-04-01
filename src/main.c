#include "physics/body.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_BALLS 20
#define BALL_RADIUS 20
#define SPAWN_INTERVAL 0.8f

int main(void) {
    const int screen_width = 1280;
    const int screen_height = 720;

    InitWindow(screen_width, screen_height, "mangoX - Physics Engine");
    SetTargetFPS(60);

    Body balls[MAX_BALLS] = {0};
    int active[MAX_BALLS] = {0};
    float spawn_timer = 0;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // spawn
        spawn_timer += dt;
        if (spawn_timer >= SPAWN_INTERVAL) {
            spawn_timer = 0;
            for (int i = 0; i < MAX_BALLS; i++) {
                if (!active[i]) {
                    float x = (float)(rand() % screen_width);
                    balls[i] = body_create((Vec2){x, -BALL_RADIUS}, 1.0f);
                    active[i] = 1;
                    break;
                }
            }
        }

        // update
        for (int i = 0; i < MAX_BALLS; i++) {
            if (!active[i]) continue;
            balls[i] = body_update(balls[i], dt);
            if (balls[i].position.y > screen_height + BALL_RADIUS)
                active[i] = 0;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("mangoX", 10, 10, 20, RAYWHITE);

        // debug
        int active_count = 0;
        for (int i = 0; i < MAX_BALLS; i++) active_count += active[i];

        char debug[128];
        snprintf(debug, sizeof(debug), "FPS: %d\ndt: %.4f\nballs: %d/%d",
                 GetFPS(), dt, active_count, MAX_BALLS);
        DrawText(debug, screen_width - 160, 10, 18, GREEN);
        for (int i = 0; i < MAX_BALLS; i++) {
            if (!active[i]) continue;
            DrawCircle((int)balls[i].position.x, (int)balls[i].position.y, BALL_RADIUS, RAYWHITE);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
