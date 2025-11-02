#include "grid.hpp"
#include <raylib.h>

void Grid::Draw()
{
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            Color color = cells[r][c] ? Color{0, 255, 0, 255} : Color{55, 55, 55, 255};
            DrawRectangle(c * cellSize, r * cellSize, cellSize-1, cellSize-1, color);
        }
    }
}

void Grid::SetCell(int row, int col, int value)
{
    if (IsWithinBounds(row, col)) {
        cells[row][col] = value;
    }
}

int Grid::GetCell(int row, int col)
{
    if (IsWithinBounds(row, col)) {
        return cells[row][col];
    }

    return 0;
}

bool Grid::IsWithinBounds(int row, int col)
{
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return true;
    }

    return false;
}
