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

void Simulation::Update()
{
    for (int r = 0; r < grid.GetRows(); r++) {
        for (int c = 0; c < grid.GetCols(); c++) {
            int liveNeighbors = CountLiveNeighbors(r, c);
            int cellValue = grid.GetCell(r, c);

            int nextValue = 0;
            if (cellValue == 1) {
                // Live cell survives if it has 2 or 3 live neighbors
                if(liveNeighbors == 2 || liveNeighbors == 3) {
                    nextValue = 1;
                }
            } else {
                // Dead cell becomes alive if it has exactly 3 live neighbors
                if (liveNeighbors == 3) {
                    nextValue = 1;
                }
            }

            tempGrid.SetCell(r, c, nextValue);
        }
    }

    grid = tempGrid;
}
