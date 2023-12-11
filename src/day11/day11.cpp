#include "day11/day11.hpp"

long Day11Solver::solveGrid(Grid<char> &grid)
{
    int rowIdx = 0;
    std::map<int, int> rowDotCount;
    std::map<int, int> colDotCount;
    for (int rowIdx = 0; rowIdx < grid.height(); rowIdx++)
    {
        for (int colIdx = 0; colIdx < grid.width(); colIdx++)
        {
            if (grid.get(colIdx, rowIdx) == '.')
            {
                rowDotCount[rowIdx]++;
                colDotCount[colIdx]++;
            }
        }
    }

    int inserted = 0;
    for (auto rowDotPair : rowDotCount)
    {
        if (rowDotPair.second == colDotCount.size())
        {
            auto newRow = std::vector<char>(grid.width(), '.');
            grid.insertRow(rowDotPair.first + inserted++, newRow);
        }
    }

    inserted = 0;
    for (auto colDotPair : colDotCount)
    {
        if (colDotPair.second == rowDotCount.size())
        {
            auto newCol = std::vector<char>(grid.height(), '.');
            grid.insertCol(colDotPair.first + inserted++, newCol);
        }
    }

    auto stars = grid.findAll('#');
    int sum = 0;
    for (auto s1 : stars)
    {
        for (auto s2 : stars)
        {
            sum += std::abs(s1.x - s2.x) + std::abs(s1.y - s2.y);
        }
    }

    return sum / 2;
}

long Day11Solver::solveGrid2(Grid<char> &grid)
{
    int EXPANSION = 1000000 - 1;

    int rowIdx = 0;
    std::map<int, int> rowDotCount;
    std::map<int, int> colDotCount;
    for (int rowIdx = 0; rowIdx < grid.height(); rowIdx++)
    {
        for (int colIdx = 0; colIdx < grid.width(); colIdx++)
        {
            if (grid.get(colIdx, rowIdx) == '.')
            {
                rowDotCount[rowIdx]++;
                colDotCount[colIdx]++;
            }
        }
    }

    auto stars = grid.findAll('#');
    long sum = 0;
    for (auto &s1 : stars)
    {
        for (auto &s2 : stars)
        {
            if (s1 == s2)
            {
                continue;
            }
            for (int i = std::min(s1.x, s2.x); i < std::max(s1.x, s2.x); i++)
            {
                if (colDotCount[i] == grid.height())
                {
                    sum += EXPANSION;
                }
                sum += 1;
            }

            for (int i = std::min(s1.y, s2.y); i < std::max(s1.y, s2.y); i++)
            {
                if (rowDotCount[i] == grid.width())
                {
                    sum += EXPANSION;
                }
                sum += 1;
            }
        }
    }

    return sum / 2;
}