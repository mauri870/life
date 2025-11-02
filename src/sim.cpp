#include "sim.hpp"
#include <vector>
#include <utility>

void Simulation::Draw()
{
    grid.Draw();
}

void Simulation::SetCellValue(int row, int col, int value)
{
    grid.SetCell(row, col, value);
}

int Simulation::CountLiveNeighbors(int row, int col)
{
    int liveNeighbors = 0;
    std::vector<std::pair<int, int>> neighborOffsets = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1},
        {-1, -1},
        {-1, 1},
        {1, -1},
        {1, 1},
    };

    // Count neighbors, toroidal grid
    for (const auto& offset : neighborOffsets) {
        int nRow = (row + offset.first + grid.GetRows()) % grid.GetRows();
        int nCol = (col + offset.second + grid.GetCols()) % grid.GetCols();

        liveNeighbors += grid.GetCell(nRow, nCol);
    }

    return liveNeighbors;
}
