#include "collision/aabb.h"
#include "collision/circle.h"
#include "physics/body.h"
#include "raylib.h"
#include <stdio.h>

#define BALL_RADIUS 20
#define BOX_W 60.0f
#define BOX_H 60.0f
#define HORIZ_FORCE 2000.0f

int main(void) {
    const int screen_width = 1280;
    const int screen_height = 720;

    InitWindow(screen_width, screen_height, "mangoX - Physics Engine");
    SetTargetFPS(60);

    // Circle pair
    Body ca = body_create((Vec2){100, screen_height / 2 - 80}, 1.0f);
    ca.radius = BALL_RADIUS;
    ca.velocity = (Vec2){200.0f, 0};

    Body cb = body_create((Vec2){screen_width - 100, screen_height / 2 - 80}, 1.0f);
    cb.radius = BALL_RADIUS;
    cb.velocity = (Vec2){-200.0f, 0};

    // AABB pair
    AABB box = {BOX_W, BOX_H};

    Body ba = body_create((Vec2){100, screen_height / 2 + 80}, 1.0f);
    ba.velocity = (Vec2){200.0f, 0};

    Body bb = body_create((Vec2){screen_width - 100, screen_height / 2 + 80}, 1.0f);
    bb.velocity = (Vec2){-200.0f, 0};

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        ca = body_update(ca, dt);
        cb = body_update(cb, dt);
        ba = body_update(ba, dt);
        bb = body_update(bb, dt);

        bool circle_hit = circle_intersects(ca, cb);
        if (circle_hit)
            circle_resolve(&ca, &cb);

        bool box_hit = aabb_check(box, ba.position, box, bb.position);
        if (box_hit)
            aabb_resolve(box, &ba, box, &bb);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("mangoX", 10, 10, 20, RAYWHITE);

        char debug[128];
        snprintf(debug, sizeof(debug), "FPS: %d\ncircle: %s\naabb:   %s", GetFPS(),
                 circle_hit ? "HIT" : "---", box_hit ? "HIT" : "---");
        DrawText(debug, screen_width - 180, 10, 18, GREEN);

        // circles
        DrawCircle((int)ca.position.x, (int)ca.position.y, BALL_RADIUS, circle_hit ? RED : BLUE);
        DrawCircle((int)cb.position.x, (int)cb.position.y, BALL_RADIUS, circle_hit ? RED : GREEN);

        // boxes
        DrawRectangle((int)(ba.position.x - BOX_W / 2), (int)(ba.position.y - BOX_H / 2),
                      (int)BOX_W, (int)BOX_H, box_hit ? RED : BLUE);
        DrawRectangle((int)(bb.position.x - BOX_W / 2), (int)(bb.position.y - BOX_H / 2),
                      (int)BOX_W, (int)BOX_H, box_hit ? RED : GREEN);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
