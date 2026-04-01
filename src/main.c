#include "raylib.h"

int main(void) {
    const int screen_width = 1280;
    const int screen_height = 720;

    InitWindow(screen_width, screen_height, "mangoX - Physics Engine");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("mangoX", 10, 10, 20, RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
