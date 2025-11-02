#pragma once
#include <vector>
#include <raylib.h>

class Grid {
public:
    Grid(int width, int height, int cellSize) {
        texture = {0};
        UpdateSize(width, height, cellSize);
    }

    ~Grid() {
        Cleanup();
    }

    void Cleanup(); // Safe cleanup method
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
    void UpdateTexture();
    void SwapCells(Grid& other); // Swap only cell data, not textures
private:
    int rows;
    int cols;
    int cellSize;
    std::vector<std::vector<int>> cells;

    // Texture rendering for performance
    Texture2D texture;
    std::vector<unsigned char> textureData;
};