#include <iostream>
#include <vector>
#include <memory>

#include "solver.hpp"
#include "day01.cpp"
#include "day02.cpp"
#include "day03.cpp"
#include "day04.cpp"
#include "day05.cpp"
#include "day06.cpp"
#include "day07/day07.hpp"
#include "day08/day08.hpp"
#include "day09/day09.hpp"
#include "day10/day10.hpp"
#include "day11/day11.hpp"
#include "day12/day12.hpp"
#include "day13/day13.hpp"
#include "day14/day14.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " day_number" << std::endl;
        return 1;
    }

    std::vector<std::unique_ptr<Solver>> solvers;
    solvers.push_back(std::make_unique<Day1Solver>());
    solvers.push_back(std::make_unique<Day2Solver>());
    solvers.push_back(std::make_unique<Day3Solver>());
    solvers.push_back(std::make_unique<Day4Solver>());
    solvers.push_back(std::make_unique<Day5Solver>());
    solvers.push_back(std::make_unique<Day6Solver>());
    solvers.push_back(std::make_unique<Day7Solver>());
    solvers.push_back(std::make_unique<Day8Solver>());
    solvers.push_back(std::make_unique<Day9Solver>());
    solvers.push_back(std::make_unique<Day10Solver>());
    solvers.push_back(std::make_unique<Day11Solver>());
    solvers.push_back(std::make_unique<Day12Solver>());
    solvers.push_back(std::make_unique<Day13Solver>());
    solvers.push_back(std::make_unique<Day14Solver>());

    std::string day = argv[1];
    std::string part = argv[2];

    // Iterate through solvers and find the one for the given day
    for (auto &solver : solvers)
    {
        if (solver->getDay() == day)
        {
            std::cout << "Day " << day << " Part " << part << std::endl;

            if (part == "1")
            {
                std::cout << solver->solve() << std::endl;
            }
            else
            {
                std::cout << solver->solve2() << std::endl;
            }

            return 0;
        }
    }

    std::cerr << "No solver registered for:" << day << std::endl;

    return 0;
}