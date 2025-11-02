#include <iostream>
#include "sim.hpp"
#include <raylib.h>
#include <GLFW/glfw3.h>

int main(void) {
// Force X11 on Linux, wayland has issues with fullscreen
#if defined(__linux__)
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
#endif

    static Color BACKGROUND_COLOR = {29, 29, 29, 255};
    static Color HELP_COLOR = {250, 250, 180, 255};
    const int N = 750;
    const int INITIAL_WINDOW_WIDTH = N;
    const int INITIAL_WINDOW_HEIGHT = N;
    const int SIM_WIDTH = 2000;
    const int SIM_HEIGHT = 2000;
    int CELL_SIZE = 5;
    int FPS = 30;

    InitWindow(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, "Mauri's Game of Life");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(FPS);

    Simulation simulation(SIM_WIDTH, SIM_HEIGHT, CELL_SIZE);

    // --- Camera for zoom & pan ---
    Camera2D camera = { 0 };
    camera.target = { 0.0f, 0.0f };
    camera.offset = { 0.0f, 0.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Simulation loop
    while (!WindowShouldClose()) {
        // Toggle cell on left mouse click
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();
            Vector2 world = GetScreenToWorld2D(mouse, camera);
            int row = world.y / CELL_SIZE;
            int col = world.x / CELL_SIZE;
            simulation.ToggleCell(row, col);
        }

        // Zoom
        float wheel = GetMouseWheelMove();
        if (wheel != 0.0f) {
            Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
            camera.zoom += wheel * 0.1f;
            if (camera.zoom < 0.1f) camera.zoom = 0.1f;
            if (camera.zoom > 10.0f) camera.zoom = 10.0f;

            Vector2 mouseWorldAfter = GetScreenToWorld2D(GetMousePosition(), camera);
            camera.target.x += (mouseWorld.x - mouseWorldAfter.x);
            camera.target.y += (mouseWorld.y - mouseWorldAfter.y);
        }

        // Pan
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            Vector2 delta = GetMouseDelta();
            delta.x /= camera.zoom;
            delta.y /= camera.zoom;
            camera.target.x -= delta.x;
            camera.target.y -= delta.y;
        }

        // Controls
        if (IsKeyPressed(KEY_SPACE)) simulation.ToggleRun();
        else if (IsKeyPressed(KEY_R)) simulation.CreateRandomState();
        else if (IsKeyPressed(KEY_C)) simulation.ClearGrid();
        else if (IsKeyPressed(KEY_E)) { FPS += 3; SetTargetFPS(FPS); }
        else if (IsKeyPressed(KEY_Q)) { if (FPS > 5) { FPS -= 2; SetTargetFPS(FPS); } }
        else if (IsKeyPressed(KEY_ENTER)) {
            ToggleFullscreen();
        }

        simulation.Update();

        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);

        BeginMode2D(camera);
        simulation.Draw();
        EndMode2D();

        DrawText(
            "Left click: Toggle cell    |   Right drag: Pan view    |   Scroll: Zoom\n"
            "Space: Run/Pause    |   R: Randomize    |   C: Clear\n"
            "E: Faster    |   Q: Slower    |   Enter: Toggle fullscreen",
            10, 10, 20, HELP_COLOR
        );
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
