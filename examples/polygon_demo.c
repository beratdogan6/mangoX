#include "collision/sat.h"
#include "physics/body.h"
#include "raylib.h"
#include <math.h>

#define NUM_BODIES 6

typedef struct {
    Body body;
    Polygon shape;
    Color color;
} Entity;

static void draw_polygon_filled(Polygon poly, Vec2 pos, Color color) {
    for (int i = 1; i < poly.count - 1; i++) {
        Vector2 v0 = {poly.verts[0].x + pos.x, poly.verts[0].y + pos.y};
        Vector2 v1 = {poly.verts[i].x + pos.x, poly.verts[i].y + pos.y};
        Vector2 v2 = {poly.verts[i + 1].x + pos.x, poly.verts[i + 1].y + pos.y};
        DrawTriangle(v0, v1, v2, color);
    }
}

static void draw_polygon_outline(Polygon poly, Vec2 pos, Color color) {
    for (int i = 0; i < poly.count; i++) {
        int j = (i + 1) % poly.count;
        DrawLine((int)(poly.verts[i].x + pos.x), (int)(poly.verts[i].y + pos.y),
                 (int)(poly.verts[j].x + pos.x), (int)(poly.verts[j].y + pos.y), color);
    }
}

static void bounce_walls(Body *b, int w, int h) {
    if (b->position.x < 50.0f) {
        b->position.x = 50.0f;
        b->velocity.x = fabsf(b->velocity.x);
    }
    if (b->position.x > w - 50) {
        b->position.x = w - 50.0f;
        b->velocity.x = -fabsf(b->velocity.x);
    }
    if (b->position.y < 50.0f) {
        b->position.y = 50.0f;
        b->velocity.y = fabsf(b->velocity.y);
    }
    if (b->position.y > h - 50) {
        b->position.y = h - 50.0f;
        b->velocity.y = -fabsf(b->velocity.y);
    }
}

int main(void) {
    const int W = 1280, H = 720;
    InitWindow(W, H, "mangoX - Physics Engine");
    SetTargetFPS(1000);

    Entity entities[NUM_BODIES] = {
        {body_create((Vec2){200, 200}, 1.0f), polygon_make_triangle(40), ORANGE},
        {body_create((Vec2){600, 180}, 1.0f), polygon_make_rect(80, 50), SKYBLUE},
        {body_create((Vec2){900, 300}, 1.0f), polygon_make_regular(5, 45), LIME},
        {body_create((Vec2){300, 500}, 1.0f), polygon_make_regular(6, 40), VIOLET},
        {body_create((Vec2){700, 450}, 1.0f), polygon_make_triangle(35), YELLOW},
        {body_create((Vec2){1050, 200}, 1.0f), polygon_make_regular(8, 42), PINK},
    };

    entities[0].body.velocity = (Vec2){180, 130};
    entities[1].body.velocity = (Vec2){-150, 160};
    entities[2].body.velocity = (Vec2){120, -170};
    entities[3].body.velocity = (Vec2){-140, -120};
    entities[4].body.velocity = (Vec2){160, -90};
    entities[5].body.velocity = (Vec2){-130, 150};

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        for (int i = 0; i < NUM_BODIES; i++) {
            entities[i].body = body_update(entities[i].body, dt);
            bounce_walls(&entities[i].body, W, H);
        }

        for (int i = 0; i < NUM_BODIES; i++) {
            for (int j = i + 1; j < NUM_BODIES; j++) {
                if (sat_check(entities[i].shape, entities[i].body.position, entities[j].shape,
                              entities[j].body.position)) {
                    sat_resolve(entities[i].shape, &entities[i].body, entities[j].shape,
                                &entities[j].body);
                }
            }
        }

        BeginDrawing();
        ClearBackground((Color){15, 15, 25, 255});

        for (int i = 0; i < NUM_BODIES; i++) {
            Color fill = entities[i].color;
            fill.a = 80;
            Color outline = entities[i].color;
            draw_polygon_filled(entities[i].shape, entities[i].body.position, fill);
            draw_polygon_outline(entities[i].shape, entities[i].body.position, outline);
        }

        DrawText("mangoX", 10, 10, 28, RAYWHITE);
        DrawFPS(10, 44);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
