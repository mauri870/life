#include "grid.hpp"
#include <raylib.h>
#include <cstdio>

void Grid::Draw()
{
    if (texture.id > 0) {
        // Update and draw texture for large grids
        UpdateTexture();
        DrawTextureEx(texture, Vector2{0, 0}, 0.0f, 1.0f, WHITE);
    } else {
        // Fallback for small grids
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                Color color = cells[r][c] ? Color{0, 255, 0, 255} : Color{55, 55, 55, 255};
                DrawRectangle(c * cellSize, r * cellSize, cellSize - 1, cellSize - 1, color);
            }
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

void Grid::FillRandom()
{
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int randValue = GetRandomValue(0, 3) == 0;
            SetCell(r, c, randValue);
        }
    }
}

void Grid::Clear()
{
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            SetCell(r, c, 0);
        }
    }
}

void Grid::ToggleCell(int row, int col)
{
    if (!IsWithinBounds(row, col)) {
        return;
    }

    SetCell(row, col, !GetCell(row, col));
}



void Grid::UpdateSize(int width, int height, int cellsize)
{
    cellSize = cellsize;
    cols = width / cellSize;
    rows = height / cellSize;
    cells.resize(rows);
    for (int r = 0; r < rows; r++) {
        cells[r].resize(cols);
    }

    // Clean up old texture safely
    Cleanup();

    // Create texture for large grids
    if (rows > 50 && cols > 50) {
        int textureWidth = cols * cellSize;
        int textureHeight = rows * cellSize;
        textureData.resize(textureWidth * textureHeight * 4); // RGBA

        // Initialize with grid pattern
        for (int y = 0; y < textureHeight; y++) {
            for (int x = 0; x < textureWidth; x++) {
                int idx = (y * textureWidth + x) * 4;

                // Check if we're on a grid line (right or bottom edge of cell)
                bool isGridLine = (x % cellSize == cellSize - 1) || (y % cellSize == cellSize - 1);

                if (isGridLine) {
                    // Grid lines - dark
                    textureData[idx + 0] = 20;   // R
                    textureData[idx + 1] = 20;   // G
                    textureData[idx + 2] = 20;   // B
                    textureData[idx + 3] = 255;  // A
                } else {
                    // Dead cell - gray
                    textureData[idx + 0] = 55;   // R
                    textureData[idx + 1] = 55;   // G
                    textureData[idx + 2] = 55;   // B
                    textureData[idx + 3] = 255;  // A
                }
            }
        }

        // Create texture
        Image img = {
            .data = textureData.data(),
            .width = textureWidth,
            .height = textureHeight,
            .mipmaps = 1,
            .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
        };

        texture = LoadTextureFromImage(img);
        SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    }
}

void Grid::UpdateTexture()
{
    if (texture.id == 0 || textureData.empty()) return;

    int textureWidth = cols * cellSize;

    // Update only the cell areas (not grid lines)
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            // Update the cell area (excluding grid lines)
            for (int dy = 0; dy < cellSize - 1; dy++) {
                for (int dx = 0; dx < cellSize - 1; dx++) {
                    int x = c * cellSize + dx;
                    int y = r * cellSize + dy;
                    int idx = (y * textureWidth + x) * 4;

                    if (cells[r][c]) {
                        // Alive cell - green
                        textureData[idx + 0] = 0;     // R
                        textureData[idx + 1] = 255;   // G
                        textureData[idx + 2] = 0;     // B
                        textureData[idx + 3] = 255;   // A
                    } else {
                        // Dead cell - gray
                        textureData[idx + 0] = 55;    // R
                        textureData[idx + 1] = 55;    // G
                        textureData[idx + 2] = 55;    // B
                        textureData[idx + 3] = 255;   // A
                    }
                }
            }
        }
    }

    // Update the GPU texture
    UpdateTextureRec(texture, Rectangle{0, 0, (float)textureWidth, (float)(rows * cellSize)}, textureData.data());
}

void Grid::SwapCells(Grid& other)
{
    // Only swap the cell data, not the texture or other resources
    std::swap(cells, other.cells);
}

void Grid::Cleanup()
{
    // Safe texture cleanup
    if (texture.id > 0) {
        // Check if we're still in a valid OpenGL context
        try {
            UnloadTexture(texture);
        } catch (...) {
            // Ignore cleanup errors during shutdown
        }
        texture.id = 0;
    }
    textureData.clear();
}
