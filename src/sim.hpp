#pragma once

#include "grid.hpp"

class Simulation {
    public:
        Simulation(int width, int height, int cellSize)
        : grid(width, height, cellSize), nextGrid(width, height, cellSize), run(false) {
            // grid.FillRandom();
        };
        void Draw();
        void SetCellValue(int row, int col, int value);
        int CountLiveNeighbors(int row, int col);
        void Update();
        void Start() { run = true; }
        void Stop() { run = false; }
        void ToggleRun() { run = !run; }
        bool IsRunning() { return run; }
        void CreateRandomState();
        void ClearGrid();
        void ToggleCell(int row, int col);
        void SetSize(int width, int height, int cellsiz) {
            grid.UpdateSize(width, height, cellsiz);
            nextGrid.UpdateSize(width, height, cellsiz);
        }
    private:
        Grid grid;
        Grid nextGrid;
        bool run;
};
