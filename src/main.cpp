#include <iostream>

#include "sim.hpp"

#include <raylib.h>
#include <GLFW/glfw3.h>

int main(void) {
    // Wayland is not fully supported in GLFW
    // this will force using X11 on wayland (XWayland)
#if defined(__linux__)
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
#endif

    static Color BACKGROUND_COLOR = {29, 29, 29, 255};
    const int N = 750;
    const int INITIAL_WINDOW_WIDTH = N;
    const int INITIAL_WINDOW_HEIGHT = N;
    int CELL_SIZE = 4;
    int FPS = 12;

    InitWindow(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, "Mauri's Game of Life");
    SetTargetFPS(FPS);

    Simulation simulation(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, CELL_SIZE);

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
        } else if (IsKeyPressed(KEY_ENTER)) {
            if (!IsWindowFullscreen()) {
                int monitor = GetCurrentMonitor();
                int screenWidth = GetMonitorWidth(monitor);
                int screenHeight = GetMonitorHeight(monitor);

                SetWindowSize(screenWidth, screenHeight);
                ToggleFullscreen();

                simulation.SetSize(screenWidth, screenHeight, CELL_SIZE);
            } else {
                ToggleFullscreen(); // exit fullscreen first
                SetWindowSize(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT);

                simulation.SetSize(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, CELL_SIZE);
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