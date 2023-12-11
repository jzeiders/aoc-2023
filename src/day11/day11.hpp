#include "solver.hpp"
#include "graph/graph.hpp"

class Day11Solver : public GridSolver
{
public:
    std::string getDay() override
    {
        return "11";
    }

    long solveGrid(Grid<char> &grid) override;
    long solveGrid2(Grid<char> &grid) override;
};