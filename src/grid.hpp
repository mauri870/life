#pragma once
#include <vector>

class Grid {
public:
    Grid(int width, int height, int cellSize)
    : rows(height / cellSize), cols(width / cellSize), cellSize(cellSize) {
        cells.resize(rows, std::vector<int>(cols, 0));
    }
    void Draw();
    void SetCell(int row, int col, int value);
private:
    int rows;
    int cols;
    int cellSize;
    std::vector<std::vector<int>> cells;
};