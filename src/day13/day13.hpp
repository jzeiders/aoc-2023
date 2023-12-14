#include "solver.hpp"
#include "grid.hpp"

class Day13Solver : public Solver
{
public:
    std::string getDay() override
    {
        return "13";
    }

    long solution(std::ifstream *file) override;

    long solution2(std::ifstream *file) override;

private:
};