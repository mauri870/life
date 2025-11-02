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
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePos = GetMousePosition();
            int row = mousePos.y / CELL_SIZE;
            int col = mousePos.x / CELL_SIZE;
            simulation.ToggleCell(row, col);
        }
        if (IsKeyPressed(KEY_SPACE)) {
            simulation.ToggleRun();
        } else if (IsKeyPressed(KEY_R)) {
            simulation.CreateRandomState();
        } else if (IsKeyPressed(KEY_C)) {
            simulation.ClearGrid();
        } else if (IsKeyPressed(KEY_E)) {
            FPS += 3;
            SetTargetFPS(FPS);
        } else if (IsKeyPressed(KEY_Q)) {
            if (FPS > 5) {
                FPS -= 2;
                SetTargetFPS(FPS);
            }
        }

        // State update
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