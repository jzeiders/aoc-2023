#include "solver.hpp"
#include "graph/graph.hpp"

class Day8Solver : public Solver
{
public:
    std::string getDay() override
    {
        return "8";
    }

    long solution(std::ifstream *file) override;

    long solution2(std::ifstream *file) override;

private:
    int solutionToZ(DirectedGraph<std::string, std::string> graph, std::string start, std::string pattern);
};