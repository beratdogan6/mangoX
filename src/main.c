#include "raylib.h"

int main(void) {
    InitWindow(1280, 720, "mangoX");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground((Color){15, 15, 25, 255});
        DrawText("mangoX", 10, 10, 28, RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
