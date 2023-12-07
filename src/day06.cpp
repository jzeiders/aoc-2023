#ifndef SRC_DAY06_HPP
#define SRC_DAY06_HPP

#include "solver.hpp"
#include "common/common.hpp"

#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>

static int computeDistance(int totalTime, int chargeTime)
{
    return chargeTime * (totalTime - chargeTime);
}

static std::vector<int> possibilities(int totalTime)
{
    std::vector<int> result;
    for (int i = 0; i < totalTime; i++)
    {
        result.push_back(computeDistance(totalTime, i));
    }
    return result;
}

static long possibilitiesQuick(long totalTime, long dist)
{
    double term = std::sqrt(totalTime * totalTime - 4 * dist);
    double lower = (totalTime - term) / 2;
    double upper = (totalTime + term) / 2;
    return floor(upper) - ceil(lower) + 1;
}

class Day6Solver : public Solver
{

    struct Input
    {
        std::vector<int> times;
        std::vector<int> dist;
    };

public:
    std::string getDay() override
    {
        return "6";
    }

    int solution(std::ifstream *file) override
    {
        auto input = parse(file);
        int result = 1;
        for (int i = 0; i < input.times.size(); i++)
        {
            auto scores = possibilities(input.times[i]);
            // Filter greater than dist[i]
            scores.erase(std::remove_if(scores.begin(), scores.end(), [input, i](int score)
                                        { return score <= input.dist[i]; }),
                         scores.end());
            result *= scores.size();
        }
        return result;
    }

    int solution2(std::ifstream *file) override
    {
        // Concatenate input
        auto input = parse(file);
        std::string timeString;
        std::string distString;

        for (auto time : input.times)
        {
            timeString += std::to_string(time);
        }

        for (auto dist : input.dist)
        {
            distString += std::to_string(dist);
        }

        long time = std::stol(timeString);
        long dist = std::stol(distString);

        return possibilitiesQuick(time, dist);
    }

private:
    Input parse(std::ifstream *file)
    {
        std::vector<std::string> lines;
        if (file->is_open())
        {
            std::string line;
            while (getline(*file, line))
            {
                lines.push_back(line);
            }
            file->close();
        }

        std::stringstream lss(lines[0]);
        std::string token;
        std::getline(lss, token, ':');
        Input input;
        while (lss >> token)
        {
            input.times.push_back(std::stoi(token));
        }

        std::stringstream lss2(lines[1]);
        std::getline(lss2, token, ':');
        while (lss2 >> token)
        {
            input.dist.push_back(std::stoi(token));
        }

        return input;
    }
};
#endif