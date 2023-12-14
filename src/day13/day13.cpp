#include "day13/day13.hpp"
#include "grid.hpp"
#include <numeric>
#include "common/common.hpp"

using Input = std::vector<Grid<char>>;

Input parseInput(std::ifstream *file)
{

    std::vector<std::string> lines;
    if (file->is_open())
    {
        std::string line;
        while (getline(*file, line))
        {
            lines.push_back(line);
        }
        file->close();
    }

    Input input;
    std::vector<std::vector<char>> rows;
    for (auto it = lines.begin(); it != lines.end(); ++it)
    {
        // Reset on blank line
        if (*it == "")
        {
            input.push_back(Grid<char>(rows));
            rows.clear();
            continue;
        }
        std::vector<char> row(it->begin(), it->end());
        rows.push_back(row);
    }
    input.push_back(Grid<char>(rows));

    return input;
}

bool reflectsAtCol(const Grid<char> &grid, int col)
{
    int diff = 0;
    while (col - diff >= 0 && col + diff + 1 < grid.width())
    {
        for (int y = 0; y < grid.height(); y++)
        {
            if (grid.get(Point(col - diff, y)) != grid.get(Point(col + diff + 1, y)))
            {
                return false;
            }
        }
        diff++;
    }
    return true;
}

bool reflectsAtRow(const Grid<char> &grid, int row)
{
    int diff = 0;
    while (row - diff >= 0 && row + diff + 1 < grid.height())
    {
        for (int x = 0; x < grid.width(); x++)
        {
            if (grid.get(Point(x, row - diff)) != grid.get(Point(x, row + diff + 1)))
            {
                return false;
            }
        }
        diff++;
    }
    return true;
}

long solveGrid(const Grid<char> &grid, int existingAnswer = -1)
{
    for (int col = 0; col < grid.width() - 1; col++)
    {
        if (reflectsAtCol(grid, col))
        {
            if (col + 1 != existingAnswer)
            {
                return (col + 1);
            }
        }
    }
    for (int row = 0; row < grid.height() - 1; row++)
    {
        if (reflectsAtRow(grid, row))
        {
            if ((row + 1) * 100 != existingAnswer)
            {
                return (row + 1) * 100;
            }
        }
    }
    return -1;
}

long Day13Solver::solution(std::ifstream *file)
{
    auto input = parseInput(file);
    std::vector<long> answers;
    for (auto grid : input)
    {
        answers.push_back(solveGrid(grid));
    }
    return std::accumulate(answers.begin(), answers.end(), 0);
}

long solveGrid2(Grid<char> &grid)
{
    long baseAnswer = solveGrid(grid);
    for (int i = 0; i < grid.width(); i++)
    {
        for (int j = 0; j < grid.height(); j++)
        {
            auto point = Point(i, j);
            char temp = grid.get(point);
            grid.set(point, temp == '#' ? '.' : '#');
            long answer = solveGrid(grid, baseAnswer);
            if (answer != -1)
            {
                return answer;
            }
            grid.set(point, temp);
        }
    }
    throw std::runtime_error("No answer found!");
}

long Day13Solver::solution2(std::ifstream *file)
{
    auto input = parseInput(file);
    std::vector<long> answers;
    for (auto &grid : input)
    {
        answers.push_back(solveGrid2(grid));
    }
    print(answers);
    return std::accumulate(answers.begin(), answers.end(), 0);
}
