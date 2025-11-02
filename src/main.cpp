#include <iostream>

#include "grid.hpp"

#include <raylib.h>

int main(void) {
    Color BACKGROUND_COLOR = {29, 29, 29, 255};
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 800;
    const int CELL_SIZE = 20;
    int FPS = 12;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mauri's Game of Life");
    SetTargetFPS(FPS);

    Grid grid(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);

    // Simulation loop
    while (!WindowShouldClose()) {
        // Event handling
        // Update state
        // Drawing
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        grid.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}