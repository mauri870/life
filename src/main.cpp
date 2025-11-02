#include <iostream>

#include "sim.hpp"

#include <raylib.h>

int main(void) {
    Color BACKGROUND_COLOR = {29, 29, 29, 255};
    const int N = 750;
    const int WINDOW_WIDTH = N;
    const int WINDOW_HEIGHT = N;
    const int CELL_SIZE = 25;
    int FPS = 12;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mauri's Game of Life");
    SetTargetFPS(FPS);

    Simulation simulation(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);

    // Simulation loop
    while (!WindowShouldClose()) {
        // Event handling
        // Update state
        simulation.Update();

        // Drawing
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        simulation.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}