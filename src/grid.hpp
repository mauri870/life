#pragma once
#include <vector>

class Grid {
public:
    Grid(int width, int height, int cellSize) {
        UpdateSize(width, height, cellSize);
    }
    void Draw();
    void SetCell(int row, int col, int value);
    int GetCell(int row, int col);
    bool IsWithinBounds(int row, int col);
    int GetRows() { return rows; } 
    int GetCols() { return cols; } 
    void FillRandom();
    void Clear();
    void ToggleCell(int row, int col);
    void UpdateSize(int width, int height, int cellsize);
private:
    int rows;
    int cols;
    int cellSize;
    std::vector<std::vector<int>> cells;
};