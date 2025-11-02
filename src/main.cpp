#include <iostream>
#include "sim.hpp"
#include <raylib.h>
#include <GLFW/glfw3.h>

const int INITIAL_WINDOW_WIDTH = 800;
const int INITIAL_WINDOW_HEIGHT = 600;

int ProcessInput(Camera2D& camera, Simulation& simulation, float& UPS_STEP, bool& HIDE_UI, const int CELL_SIZE);

int main(void) {
// Force X11 on Linux, wayland has issues with fullscreen
#if defined(__linux__)
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
#endif

    static Color BACKGROUND_COLOR = {29, 29, 29, 255};
    const int SIM_WIDTH = 2000;
    const int SIM_HEIGHT = 2000;
    int CELL_SIZE = 5;
    float UPS_STEP = 12.0f; // simulation at 12 UPS
    float ups = 0.0f;
    bool HIDE_UI = false;

    InitWindow(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, "Mauri's Game of Life");
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    Simulation simulation(SIM_WIDTH, SIM_HEIGHT, CELL_SIZE);

    // Camera for panning and zooming
    Camera2D camera = { 0 };
    camera.target = { 0.0f, 0.0f };
    camera.offset = { 0.0f, 0.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Simulation loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        ups += dt;

        ProcessInput(camera, simulation, UPS_STEP, HIDE_UI, CELL_SIZE);

        // Update simulation at fixed timestep
        float upsStep = 1.0f / UPS_STEP;
        while (ups >= upsStep) {
            simulation.Update();
            ups -= upsStep;
        }

        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);

        BeginMode2D(camera);
        simulation.Draw();
        EndMode2D();

        // Draw UI
        if (!HIDE_UI) {
            DrawRectangle(0, 0, 700, 80, Fade(BLACK, 0.8f));
            DrawText(
                "Left click: Toggle cell    |   Right drag: Pan view    |   Scroll: Zoom\n"
                "Space: Run/Pause    |   R: Randomize    |   C: Clear   |   I: Hide UI\n"
                "E: Faster    |   Q: Slower    |   Enter: Toggle fullscreen",
                10, 10, 20, YELLOW
            );

            float ft = GetFrameTime() * 1000.0f;
            int ftMs = static_cast<int>(ft);

            char buf[64];
            sprintf(buf, "Frame Time: %d ms | FPS: %d | UPS: %d", ftMs, GetFPS(), static_cast<int>(UPS_STEP));

            int fontSize = 16;
            int w = MeasureText(buf, fontSize);
            int x = GetScreenWidth() - w - 10;
            int y = GetScreenHeight() - fontSize - 10;

            DrawRectangle(x - 2, y - 2, w + 4, fontSize + 4, Fade(BLACK, 0.8f));
            DrawText(buf, x, y, fontSize, YELLOW);
        }
        EndDrawing();
    }

    // Clean up simulation before closing window to avoid segfaults
    simulation.Cleanup();

    CloseWindow();
    return 0;
}

int ProcessInput(Camera2D& camera, Simulation& simulation, float& UPS_STEP, bool& HIDE_UI, const int CELL_SIZE)
{
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
    else if (IsKeyPressed(KEY_E)) { UPS_STEP += 3; }
    else if (IsKeyPressed(KEY_Q)) { if (UPS_STEP > 12) { UPS_STEP -= 2; } }
    else if (IsKeyPressed(KEY_I)) {
        HIDE_UI = !HIDE_UI;
    }
    else if (IsKeyPressed(KEY_ENTER)) {
        if (!IsWindowFullscreen()) {
            int monitor = GetCurrentMonitor();
            int screenWidth = GetMonitorWidth(monitor);
            int screenHeight = GetMonitorHeight(monitor);

            SetWindowSize(screenWidth, screenHeight);
            ToggleFullscreen();
            simulation.SetSize(screenWidth, screenHeight, CELL_SIZE);
        } else {
            ToggleFullscreen();
            SetWindowSize(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT);
            simulation.SetSize(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, CELL_SIZE);
        }
    }
    return 0;
}
