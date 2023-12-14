#include "solver.hpp"
#include <deque>

struct Day12Input
{
    std::string line;
    std::vector<int> lengths;
};

class Day12Solver : public LineSolver<Day12Input>
{
public:
    Day12Solver() : LineSolver() {}

    std::string getDay() override { return "12"; }

    Day12Input parse(std::string line) override;
    long solveItem(Day12Input item) override;
    long solveItem2(Day12Input item) override;
    long combine(std::vector<long> results) override;
};