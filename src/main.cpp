#include <iostream>

#include "sim.hpp"

#include <raylib.h>

int main(void) {
    Color BACKGROUND_COLOR = {29, 29, 29, 255};
    const int WINDOW_WIDTH = 750;
    const int WINDOW_HEIGHT = 750;
    const int CELL_SIZE = 25;
    int FPS = 12;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mauri's Game of Life");
    SetTargetFPS(FPS);

    Simulation simulation(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
    simulation.SetCellValue(5, 29, 1);
    simulation.SetCellValue(5, 0, 1);
    simulation.SetCellValue(4, 29, 1);


    std::cout << simulation.CountLiveNeighbors(5, 29) << std::endl;

    // Simulation loop
    while (!WindowShouldClose()) {
        // Event handling
        // Update state
        // Drawing
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        simulation.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}