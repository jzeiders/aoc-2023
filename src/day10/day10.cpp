#include "day10/day10.hpp"
#include "common/common.hpp"

inline bool DFSHelper(DirectedGraph<Point, char> &graph, Point start, std::set<Point> &visited, std::vector<Point> *path, Point parent)
{
    visited.insert(start);
    auto neighbors = graph.getNeighbors(start);
    for (auto neighbor : neighbors)
    {
        if (!graph.hasNode(neighbor))
        {
            continue;
        }
        path->push_back(start);
        if (visited.find(neighbor) == visited.end())
        {

            bool next = DFSHelper(graph, neighbor, visited, path, start);
            if (next)
            {
                return true;
            }
        }
        else if (neighbor != parent)
        {
            return true;
        }
        path->pop_back();
    }
    return false;
}

long Day10Solver::solveGrid(Grid<char> &grid)
{
    auto graph = parseGraph(grid);
    std::set<Point> visited = {};
    std::map<Point, int> distances = graph.distances(grid.find('S'));

    auto start = grid.find('S');
    auto last = Point(-1, -1);

    std::vector<Point> path = {start};

    DFSHelper(graph, start, visited, &path, last);

    return (path.size() + 1) / 2;
}

inline bool isValidPath(std::vector<Point> path)
{
    for (int i = 0; i < path.size(); i++)
    {
        std::set<Point> validNext = {path[i].up(), path[i].down(), path[i].left(), path[i].right()};
        auto next = path[(i + 1) % path.size()];
        if (validNext.find(next) == validNext.end())
        {
            std::cout << "Invalid path: " << path[i] << " -> " << next << std::endl;
            return false;
        }
    }
    std::set<Point> deduped(path.begin(), path.end());
    if (deduped.size() != path.size())
    {
        std::cout << "Path contains duplicates" << std::endl;
        return false;
    }

    return true;
}

long Day10Solver::solveGrid2(Grid<char> &grid)
{
    auto graph = parseGraph(grid);
    std::set<Point> visited = {};
    std::map<Point, int> distances = graph.distances(grid.find('S'));

    auto start = grid.find('S');
    auto last = Point(-1, -1);

    std::vector<Point> path = {};
    DFSHelper(graph, start, visited, &path, last);

    if (!isValidPath(path))
    {
        return -1;
    }

    long area = 0;

    for (int i = 0; i < path.size(); i++)
    {
        auto curr = path[i];
        auto next = path[(i + 1) % path.size()];

        area += (curr.x + next.x) * (curr.y - next.y);
    }

    if (area < 0)
    {
        area = -area;
    }

    area /= 2;

    return area - (path.size() / 2) + 1;
}

DirectedGraph<Point, char> Day10Solver::parseGraph(Grid<char> &grid)
{
    auto graph = DirectedGraph<Point, char>();
    for (int y = 0; y < grid.height(); y++)
    {
        for (int x = 0; x < grid.width(); x++)
        {
            auto pos = Point(x, y);
            char n = grid.get(pos);
            graph.addNode(pos, n);
            std::vector<Point> neigbors;
            switch (n)
            {
            case '|':
                neigbors = {pos.up(), pos.down()};
                break;
            case '-':
                neigbors = {pos.left(), pos.right()};
                break;
            case 'L':
                neigbors = {pos.up(), pos.right()};
                break;
            case 'J':
                neigbors = {pos.up(), pos.left()};
                break;
            case '7':
                neigbors = {pos.down(), pos.left()};
                break;
            case 'F':
                neigbors = {pos.down(), pos.right()};
                break;
            case 'S':
                neigbors = {pos.up(), pos.down(), pos.left(), pos.right()};
                break;
            }
            for (auto neighbor : neigbors)
            {
                graph.addEdge(pos, neighbor);
            }
        }
    }

    return graph;
}
