#ifndef SRC_DAY04_HPP
#define SRC_DAY04_HPP

#include "solver.hpp"
#include "common/common.hpp"

#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>

using Card = std::pair<std::vector<int>, std::vector<int>>;

class Day4Solver : public LineSolver<Card>
{

public:
    std::string getDay() override
    {
        return "4";
    }

    Card parse(std::string line) override
    {
        std::istringstream lineStream(line);
        std::string token;
        std::vector<int> first;
        std::vector<int> second;

        // Skip the "Card X:" part
        std::getline(lineStream, token, ':');

        // Read numbers before the pipe
        while (lineStream >> token && token != "|")
        {
            first.push_back(std::stoi(token));
        }

        // Read numbers after the pipe
        while (lineStream >> token)
        {
            second.push_back(std::stoi(token));
        }
        return std::make_pair(first, second);
    }

    int solveItem(Card card) override
    {
        std::set<int> winningNumbers(card.first.begin(), card.first.end());
        std::set<int> values(card.second.begin(), card.second.end());
        std::set<int> inter;
        std::set_intersection(winningNumbers.begin(), winningNumbers.end(), values.begin(), values.end(), std::inserter(inter, inter.begin()));

        return inter.size();
    }

    int solveItem2(Card card) override
    {
        return solveItem(card);
    }

    int combine(std::vector<int> results) override
    {
        // Sum the vector
        return combine2(results);
    }

    int combine1(std::vector<int> results)
    {
        int sum = 0;
        for (int result : results)
        {
            if (result > 0)
            {
                sum += std::pow(2, result - 1);
            }
        }
        return sum;
    }

    int combine2(std::vector<int> results)
    {
        std::vector counts = std::vector<int>(results.size(), 1);
        for (int i = 0; i < results.size(); i++)
        {
            int j = results[i] + 1;
            for (int k = 1; k < j && (i + k) < results.size(); k++)
            {
                counts[i + k] += counts[i];
            }
        }
        return sumVector(counts);
        // return combine(results);
    }
};

#endif