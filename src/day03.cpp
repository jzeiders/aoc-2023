
#include <iostream>
#include <cctype> // for isdigit
#include <algorithm>
#include <map>
#include <set>
#include "solver.hpp"

class Day3Solver : public GridSolver
{
public:
    std::string getDay() override { return "3"; }
    long solveGrid(Grid<char> &grid) override
    {
        int sum = 0;
        for (int j = 0; j < grid.height(); j++)
        {
            for (int i = 0; i < grid.width(); i++)
            {
                std::string num = "";
                std::vector<char> neighbors;
                while (i < grid.width() && isdigit(grid.get(i, j)))
                {
                    auto currentNeighors = grid.neighbors(i, j);
                    neighbors.insert(neighbors.end(), currentNeighors.begin(), currentNeighors.end());
                    num += grid.get(i, j);
                    i++;
                }
                if (num != "" && std::any_of(neighbors.begin(), neighbors.end(), [](char c)
                                             { return !isdigit(c) && c != '.'; }))
                {
                    sum += std::stoi(num);
                }
            }
        }
        return sum;
    }

    long solveGrid2(Grid<char> &grid) override
    {
        std::map<Point, std::vector<int>> gearCandidates;
        int sum = 0;
        for (int j = 0; j < grid.height(); j++)
        {
            for (int i = 0; i < grid.width(); i++)
            {
                std::string num = "";
                std::set<std::pair<Point, char>> neighbors;
                while (i < grid.width() && isdigit(grid.get(i, j)))
                {
                    auto currentNeighors = grid.neighborsWithIndex(i, j);
                    for (auto neighbor : currentNeighors)
                    {
                        neighbors.insert(neighbor);
                    }
                    num += grid.get(i, j);
                    i++;
                }
                if (num != "")
                {
                    for (auto neighbor : neighbors)
                    {
                        if (neighbor.second == '*')
                        {
                            gearCandidates[neighbor.first].push_back(std::stoi(num));
                        }
                    }
                }
            }
        }
        // Get all the candidates that have more than one gear
        for (auto candidate : gearCandidates)
        {
            if (candidate.second.size() == 2)
            {

                sum += (candidate.second[0] * candidate.second[1]);
            }
        }
        return sum;
    }
};