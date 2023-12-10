#include "solver.hpp"
#include "graph/graph.hpp"

class Day10Solver : public GridSolver
{
public:
    std::string getDay() override
    {
        return "10";
    }

    long solveGrid(Grid<char> &grid) override;
    long solveGrid2(Grid<char> &grid) override;

private:
    DirectedGraph<Point, char> parseGraph(Grid<char> &grid);
};