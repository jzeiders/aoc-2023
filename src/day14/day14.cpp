#include "day14/day14.hpp"

long scoreBoard(Grid<char> &grid)
{
    int result = 0;
    for (int i = 0; i < grid.width(); i++)
    {
        for (int j = 0; j < grid.height(); j++)
        {
            if (grid.get(Point(i, j)) == 'O')
            {
                result += (grid.height() - j);
            }
        }
    }
    return result;
}

long uniqueBoard(Grid<char> &grid)
{
    long result = 0;
    for (int i = 0; i < grid.width(); i++)
    {
        for (int j = 0; j < grid.height(); j++)
        {
            if (grid.get(Point(i, j)) == 'O')
            {
                result += grid.height() * j + i;
            }
        }
    }
    return result;
}

void slideNorth(Grid<char> &grid)
{
    for (int y = 0; y < grid.height(); y++)
    {
        for (int x = 0; x < grid.width(); x++)
        {
            auto point = Point(x, y);
            auto north = point.up();
            if (grid.get(point) == 'O')
            {
                while (north.y >= 0 && grid.get(north) == '.')
                {
                    grid.set(north, 'O');
                    grid.set(point, '.');
                    point = north;
                    north = point.up();
                }
            }
        }
    }
}

void slideSouth(Grid<char> &grid)
{
    for (int y = grid.height() - 1; y >= 0; y--)
    {
        for (int x = 0; x < grid.width(); x++)
        {
            auto point = Point(x, y);
            auto south = point.down();
            if (grid.get(point) == 'O')
            {
                while (south.y < grid.height() && grid.get(south) == '.')
                {
                    grid.set(south, 'O');
                    grid.set(point, '.');
                    point = south;
                    south = point.down();
                }
            }
        }
    }
}

void slideEast(Grid<char> &grid)
{
    for (int x = grid.width() - 1; x >= 0; x--)
    {
        for (int y = 0; y < grid.height(); y++)
        {
            auto point = Point(x, y);
            auto east = point.right();
            if (grid.get(point) == 'O')
            {
                while (east.x < grid.width() && grid.get(east) == '.')
                {
                    grid.set(east, 'O');
                    grid.set(point, '.');
                    point = east;
                    east = point.right();
                }
            }
        }
    }
}

void slideWest(Grid<char> &grid)
{
    for (int x = 0; x < grid.width(); x++)
    {
        for (int y = 0; y < grid.height(); y++)
        {
            auto point = Point(x, y);
            auto west = point.left();
            if (grid.get(point) == 'O')
            {
                while (west.x >= 0 && grid.get(west) == '.')
                {
                    grid.set(west, 'O');
                    grid.set(point, '.');
                    point = west;
                    west = point.left();
                }
            }
        }
    }
}

long Day14Solver::solveGrid(Grid<char> &grid)
{
    std::cout << grid << std::endl;
    slideNorth(grid);
    std::cout << grid << std::endl;
    return scoreBoard(grid);
}

long Day14Solver::solveGrid2(Grid<char> &grid)
{
    std::map<long, long> seen;

    // Find cycles
    int cycleLength = -1;

    for (int i = 0; i < 200; i++)
    {
        if (seen.find(uniqueBoard(grid)) != seen.end())
        {
            cycleLength = i - seen[uniqueBoard(grid)];
            break;
        }
        seen[uniqueBoard(grid)] = i;
        slideNorth(grid);
        slideWest(grid);
        slideSouth(grid);
        slideEast(grid);
    }

    if (cycleLength == -1)
    {
        throw std::runtime_error("No cycle found");
    }

    for (int i = 0; i < (1000000000 - seen.size()) % cycleLength; i++)
    {
        slideNorth(grid);
        slideWest(grid);
        slideSouth(grid);
        slideEast(grid);
    }

    return scoreBoard(grid);
}