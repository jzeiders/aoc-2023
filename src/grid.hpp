#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include "graph/graph.hpp"

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

    Point up()
    {
        return Point(x, y - 1);
    }

    Point down()
    {
        return Point(x, y + 1);
    }

    Point left()
    {
        return Point(x - 1, y);
    }

    Point right()
    {
        return Point(x + 1, y);
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &p)
    {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }

    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }
};

template <typename T>
class Grid
{
private:
    std::vector<std::vector<T>> grid;

public:
    Grid(const Grid &g) // Copy Constructor
        : grid(g.grid)
    {
    }
    // Constructor that takes a list of strings to initialize the grid
    Grid(const std::vector<std::vector<T>> &rows)
    {
        grid = rows;
    }
    Grid(int width, int height, T value)
    {
        grid = std::vector<std::vector<T>>(height, std::vector<T>(width, value));
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

    T get(Point p) const
    {
        return get(p.x, p.y);
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

    void set(Point p, T value)
    {
        set(p.x, p.y, value);
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

    // Find a value
    Point find(T value) const
    {
        for (int y = 0; y < height(); y++)
        {
            for (int x = 0; x < width(); x++)
            {
                if (get(x, y) == value)
                {
                    return Point(x, y);
                }
            }
        }
        throw std::invalid_argument("Value not found in grid");
    }

    // Find all values
    std::vector<Point> findAll(T value) const
    {
        std::vector<Point> points;
        for (int y = 0; y < height(); y++)
        {
            for (int x = 0; x < width(); x++)
            {
                if (get(x, y) == value)
                {
                    points.push_back(Point(x, y));
                }
            }
        }
        return points;
    }

    void insertRow(int rowIdx, std::vector<T> row)
    {
        grid.insert(grid.begin() + rowIdx, row);
    }

    void insertCol(int colIdx, std::vector<T> col)
    {
        for (int rowIdx = 0; rowIdx < height(); rowIdx++)
        {
            grid[rowIdx].insert(grid[rowIdx].begin() + colIdx, col[rowIdx]);
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Grid &grid)
    {
        for (auto row : grid.grid)
        {
            for (auto col : row)
            {
                os << col;
            }
            os << std::endl;
        }
        return os;
    }
};

#endif // GRID_H