#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>

struct Point
{
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}

    bool operator<(const Point &other) const
    {
        if (y == other.y)
        {
            return x < other.x;
        }
        return y < other.y;
    }
};

template <typename T>
class Grid
{
private:
    std::vector<std::vector<T>> grid;

public:
    // Constructor that takes a list of strings to initialize the grid
    Grid(const std::vector<std::vector<T>> &rows)
    {
        grid = rows;
    }

    std::vector<std::pair<Point, T>> neighborsWithIndex(int x, int y) const
    {
        std::vector<std::pair<Point, T>> neighbors;
        std::vector<std::pair<int, int>> offsets = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

        for (auto offset : offsets)
        {
            int nx = x + offset.first;
            int ny = y + offset.second;

            if (nx >= 0 && nx < this->width() && ny >= 0 && ny < this->height())
            {
                neighbors.push_back(std::make_pair(Point(nx, ny), get(nx, ny)));
            }
        }

        return neighbors;
    }

    std::vector<T> neighbors(int x, int y) const
    {
        std::vector<T> neighbors;
        std::vector<std::pair<int, int>> offsets = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

        for (auto offset : offsets)
        {
            int nx = x + offset.first;
            int ny = y + offset.second;

            if (nx >= 0 && nx < this->width() && ny >= 0 && ny < this->height())
            {
                neighbors.push_back(grid[ny][nx]);
            }
        }

        return neighbors;
    }

    // Function to get the character at a specific position
    T get(int x, int y) const
    {
        if (y >= grid.size() || x >= grid[0].size())
        {
            throw std::out_of_range("Grid coordinates out of bounds");
        }
        return grid[y][x];
    }

    void set(int x, int y, T value)
    {
        if (y >= grid.size() || x >= grid[0].size())
        {
            throw std::out_of_range("Grid coordinates out of bounds");
        }
        grid[y][x] = value;
    }

    // Function to get the height of the grid
    size_t height() const
    {
        return grid.size();
    }

    // Function to get the width of the grid
    size_t width() const
    {
        return grid.empty() ? 0 : grid[0].size();
    }
};

#endif // GRID_H