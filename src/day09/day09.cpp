#include "day09/day09.hpp"
#include "common/common.hpp"
#include <numeric>

std::vector<int> Day9Solver::parse(std::string line)
{
    std::vector<int> result;
    std::stringstream iss(line);
    std::string token;
    while (std::getline(iss, token, ' '))
    {
        result.push_back(std::stoi(token));
    }
    return result;
}

std::vector<std::vector<int>> Day9Solver::getGrid(std::vector<int> input)
{
    std::vector<std::vector<int>> grid;
    std::vector<int> row = input;
    while (!std::all_of(row.begin(), row.end(), [](int i)
                        { return i == 0; }))
    {
        grid.push_back(row);
        std::vector<int> nextRow;
        for (int i = 0; i < row.size() - 1; i++)
        {
            nextRow.push_back(row[i + 1] - row[i]);
        }
        row = nextRow;
    }
    return grid;
}

long Day9Solver::solveItem(std::vector<int> input)
{
    auto grid = getGrid(input);

    int result = 0;
    for (auto &row : grid)
    {
        result += row[row.size() - 1];
    }

    return result;
}

long Day9Solver::solveItem2(std::vector<int> input)
{
    auto grid = getGrid(input);

    int result = 0;
    for (auto it = std::rbegin(grid); it != std::rend(grid); ++it)
    {
        result = (*it)[0] - result;
    }

    return result;
}

long Day9Solver::combine(std::vector<long> results)
{
    return std::accumulate(results.begin(), results.end(), 0);
}