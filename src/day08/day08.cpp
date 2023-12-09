#include "day08/day08.hpp"
#include "common/common.hpp"
#include <algorithm>
#include "graph/graph.hpp"
#include "solver.hpp"
#include <numeric>
#include <algorithm>

struct Input
{
    std::string pattern;
    std::map<std::string, std::vector<std::string>> nodes;
};

inline Input parseFile(std::ifstream *file)
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

    Input input;
    input.pattern = lines[0];

    for (auto it = lines.begin() + 2; it != lines.end(); ++it)
    {
        std::string line = *it;
        std::stringstream iss(line);
        std::string node, l, r;

        std::getline(iss, node, ' ');
        iss.ignore(3); // Skip " = ("
        std::getline(iss, l, ',');
        iss.ignore(1); // Skip " "
        std::getline(iss, r, ')');
        input.nodes[node] = {l, r};
    }
    return input;
}

int Day8Solver::solutionToZ(DirectedGraph<std::string, std::string> graph, std::string start, std::string pattern)
{
    std::string root = start;
    int steps = 0;

    int patternPos = -1;

    while (root.back() != 'Z')
    {
        patternPos = (patternPos + 1) % pattern.size();
        auto step = pattern[patternPos];
        auto neighbors = graph.getNeighbors(root);
        if (step == 'L')
        {
            root = neighbors[0];
        }
        if (step == 'R')
        {
            root = neighbors[1];
        }
        steps += 1;
    }

    return steps;
}

long Day8Solver::solution(std::ifstream *file)
{
    auto input = parseFile(file);

    DirectedGraph<std::string, std::string> graph;
    for (auto node : input.nodes)
    {
        graph.addNode(node.first, node.first);
        graph.addEdge(node.first, node.second[0]);
        graph.addEdge(node.first, node.second[1]);
    }

    std::string root = "AAA";
    int steps = 0;

    int patternPos = -1;

    while (root != "ZZZ")
    {
        patternPos = (patternPos + 1) % input.pattern.size();
        auto step = input.pattern[patternPos];
        auto neighbors = graph.getNeighbors(root);
        print(neighbors);
        if (step == 'L')
        {
            root = neighbors[0];
        }
        if (step == 'R')
        {
            root = neighbors[1];
        }
        steps += 1;
    }

    return steps;
}

long Day8Solver::solution2(std::ifstream *file)
{
    auto input = parseFile(file);

    DirectedGraph<std::string, std::string> graph;
    for (auto node : input.nodes)
    {
        graph.addNode(node.first, node.first);
        graph.addEdge(node.first, node.second[0]);
        graph.addEdge(node.first, node.second[1]);
    }

    std::vector<int> solutions;
    for (const auto &node : input.nodes)
    {
        if (node.first.back() == 'A')
        {
            solutions.push_back(solutionToZ(graph, node.first, input.pattern));
        }
    }

    long long result = 1;
    for (int number : solutions)
    {
        result = std::lcm(result, number);
    }
    return result;
}
