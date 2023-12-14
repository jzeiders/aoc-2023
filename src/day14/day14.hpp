#include "solver.hpp"

class Day14Solver : public GridSolver
{
public:
    std::string getDay() override
    {
        return "14";
    }

    long solveGrid(Grid<char> &grid) override;
    long solveGrid2(Grid<char> &grid) override;
};