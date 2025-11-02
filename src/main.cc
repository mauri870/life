#include <iostream>

#include <raylib.h>

int main(void) {
    std::cout << "Hello, World!" << std::endl;

    InitWindow(800, 600, "Hello World");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, World!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}