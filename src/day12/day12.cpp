#include "day12/day12.hpp"
#include "common/common.hpp"
#include <numeric>
#include <sstream>
#include <deque>

Day12Input Day12Solver::parse(std::string line)
{
    Day12Input input;
    input.line = line;
    std::stringstream ss(line);
    std::string token;
    std::getline(ss, input.line, ' ');
    while (std::getline(ss, token, ','))
    {
        input.lengths.push_back(std::stoi(token));
    }
    return input;
}
inline std::vector<std::pair<char, int>> gatherRuns(const std::string &str)
{
    std::vector<std::pair<char, int>> runs;
    if (str.empty())
        return runs;

    char currentChar = str[0];
    int count = 1;

    for (size_t i = 1; i < str.length(); ++i)
    {
        if (str[i] == currentChar)
        {
            ++count;
        }
        else
        {
            runs.push_back(std::make_pair(currentChar, count));
            currentChar = str[i];
            count = 1;
        }
    }

    // Add the last run
    runs.push_back(std::make_pair(currentChar, count));

    return runs;
}

inline long directCase(std::string line, std::vector<int> lengths)
{
    auto runs = gatherRuns(line);
    auto lengthsCount = std::vector<int>();
    for (auto run : runs)
    {
        if (run.first == '#')
            lengthsCount.push_back(run.second);
    }
    return lengthsCount == lengths ? 1 : 0;
}

inline long helper(std::string line, std::vector<int> &lengths, std::map<std::string, long> &cache)
{
    if (cache.find(line) != cache.end())
        return cache[line];
    int questionMarkCount = std::count(line.begin(), line.end(), '?');
    if (questionMarkCount == 0)
    {
        int answer = directCase(line, lengths);
        cache[line] = answer;
        return answer;
    }

    int questionMarkIndex = line.find('?');
    line[questionMarkIndex] = '.';
    int take = helper(line, lengths, cache);
    line[questionMarkIndex] = '#';
    int skip = helper(line, lengths, cache);
    return take + skip;
}

long Day12Solver::solveItem(Day12Input item)
{
    std::map<std::string, long> cache;
    return helper(item.line, item.lengths, cache);
}

long Day12Solver::solveItem2(Day12Input item)
{
    return 0;
}

long Day12Solver::combine(std::vector<long> results)
{
    return std::accumulate(results.begin(), results.end(), 0);
}