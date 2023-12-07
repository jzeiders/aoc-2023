#ifndef SRC_DAY05_HPP
#define SRC_DAY05_HPP

#include "solver.hpp"
#include "common/common.hpp"

#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>

using Range = std::pair<long, long>;
class MapLine
{
    long dest;
    long start;
    long length;

public:
    MapLine(long dest, long start, long length) : dest(dest), start(start), length(length) {}

    Range getRange()
    {
        return Range(start, start + length - 1);
    }

    long getStartOfRange()
    {
        return start;
    }
    long getEndOfRange()
    {
        return start + length - 1;
    }
    long computeMappedValue(long value)
    {
        return dest + (value - start);
    }
};

using Map = std::vector<MapLine>;
using Input = std::pair<std::vector<long>, std::vector<Map>>;

inline std::vector<long> mapValues(std::vector<long> &values, Map &maps)
{
    std::vector<long> mappedValues;

    for (auto value : values)
    {
        long result = value;
        for (auto map : maps)
        {
            if (value >= map.getStartOfRange() && value < map.getEndOfRange())
            {
                result = map.computeMappedValue(value);
                break;
            }
        }
        mappedValues.push_back(result);
    }

    std::cout << "Mapped values";

    return mappedValues;
}

inline void printRanges(std::set<Range> &ranges)
{
    for (auto range : ranges)
    {
        std::cout << range.first << "-" << range.second << " ";
    }
    std::cout << std::endl;
}

inline Range overlapRanges(Range r1, Range r2)
{
    return Range(std::max(r1.first, r2.first), std::min(r1.second, r2.second));
}

inline Range shiftRange(Range range, long shift)
{
    return Range(range.first + shift, range.second + shift);
}

inline bool isRangeValid(Range range)
{
    return range.first <= range.second;
}

inline std::set<Range> splitRange(Range range, Range overlap)
{
    std::set<Range> ranges;
    if (range.first < overlap.first)
    {
        ranges.insert(Range(range.first, overlap.first - 1));
    }
    if (range.second > overlap.second)
    {
        ranges.insert(Range(overlap.second + 1, range.second));
    }
    return ranges;
}

inline std::set<Range> mapRanges(std::set<Range> &values, Map &maps)
{
    std::set<Range> mappedRanges = values;
    std::set<Range> shifted;

    bool print = true;
    for (auto mapLine : maps)
    {
        std::set<Range> results;

        for (auto range : mappedRanges)
        {
            auto overlap = overlapRanges(range, mapLine.getRange());
            if (!isRangeValid(overlap))
            {
                results.insert(range);
                continue;
            }
            auto split = splitRange(range, overlap);
            results.insert(split.begin(), split.end());
            shifted.insert(Range(mapLine.computeMappedValue(overlap.first), mapLine.computeMappedValue(overlap.second)));
        }
        mappedRanges = results;
    }

    auto result = mappedRanges;
    result.insert(shifted.begin(), shifted.end());

    return result;
}

class Day5Solver : public Solver
{

public:
    std::string getDay() override
    {
        return "5";
    }

    int solution(std::ifstream *file) override
    {
        auto input = parseInput(file);
        auto values = input.first;
        auto ranges = std::set<Range>();
        for (auto value : values)
        {
            ranges.insert(Range(value, value));
        }

        auto maps = input.second;

        for (auto map : maps)
        {
            ranges = mapRanges(ranges, map);
        }
        std::vector<long> starts;
        for (auto value : ranges)
        {
            starts.push_back(value.first);
        }

        return *std::min_element(starts.begin(), starts.end());
    }

    int solution2(std::ifstream *file) override
    {

        auto input = parseInput(file);
        auto rawValues = input.first;
        std::set<Range> values;
        for (size_t i = 0; i + 1 < rawValues.size(); i += 2)
        {
            long firstValue = rawValues[i];
            long secondValue = rawValues[i + 1];

            values.insert(Range(firstValue, firstValue + secondValue - 1));
        }

        auto maps = input.second;

        for (auto map : maps)
        {
            values = mapRanges(values, map);
        }

        std::vector<long> starts;
        for (auto value : values)
        {
            starts.push_back(value.first);
        }

        return *std::min_element(starts.begin(), starts.end());
    }

private:
    Input parseInput(std::ifstream *file)
    {
        std::vector<long> values;
        std::vector<Map> maps;

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

        std::istringstream lineStream(lines[0]);
        std::string token;

        std::getline(lineStream, token, ':');
        while (lineStream >> token)
        {
            values.push_back(std::stol(token));
        }

        Map map;
        for (auto it = lines.begin() + 2; it != lines.end(); ++it)
        {
            // Reset on blank line
            if (*it == "")
            {
                maps.push_back(map);
                map = Map();
                continue;
            }
            // Skip the name lines
            if (!std::isdigit((*it)[0]))
            {
                continue;
            }
            std::stringstream lineStream(*it);
            long key, val1, val2;
            lineStream >> key >> val1 >> val2;
            map.push_back(MapLine(key, val1, val2));
        }
        maps.push_back(map);

        return std::make_pair(values, maps);
    }
};

#endif