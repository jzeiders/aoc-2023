#include "solver.hpp"
#include "graph/graph.hpp"

class Day9Solver : public LineSolver<std::vector<int>>
{
public:
    std::string getDay() override
    {
        return "9";
    }

    std::vector<int> parse(std::string line) override;
    long solveItem(std::vector<int>) override;
    long solveItem2(std::vector<int>) override;
    long combine(std::vector<long> results) override;

private:
    std::vector<std::vector<int>> getGrid(std::vector<int> input);
};