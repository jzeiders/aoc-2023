#ifndef Day2Solver_H
#define Day2Solver_H

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <numeric>
#include <map>

#include "solver.hpp"
#include "common/common.hpp"

enum class Color
{
    Green,
    Red,
    Blue
};

static Color parseColor(const std::string &colorStr)
{
    if (colorStr == "green")
        return Color::Green;
    if (colorStr == "red")
        return Color::Red;
    if (colorStr == "blue")
        return Color::Blue;
    throw std::runtime_error("Invalid color string: " + colorStr);
};

struct Draw
{
    Color color;
    int count;
};

struct Turn
{
    std::vector<Draw> colorQuantityPairs;
};

struct Game
{
    int gameID;
    std::vector<Turn> turns;
};

static Draw parseColorQuantityPair(const std::string &str)
{
    std::istringstream iss(str);
    Draw cqp;
    std::string colorStr;
    iss >> cqp.count >> colorStr;
    cqp.color = parseColor(colorStr);
    return cqp;
}

static Turn parseTurn(const std::string &str)
{
    Turn turn;
    auto pairs = split(str, ',');
    for (auto &pair : pairs)
    {
        turn.colorQuantityPairs.push_back(parseColorQuantityPair(pair));
    }
    return turn;
}

static Game parseGame(const std::string &str)
{
    Game game;
    auto gameParts = split(str, ':');
    // Convert string to int
    game.gameID = std::stoi(split(gameParts[0], ' ')[1]);

    auto turns = split(gameParts[1], ';');
    for (auto &turn : turns)
    {
        game.turns.push_back(parseTurn(turn));
    }
    return game;
}

static bool drawIsInvalid(Draw draw)
{
    switch (draw.color)
    {
    case Color::Red:
        return draw.count > 12;
    case Color::Green:
        return draw.count > 13;
    case Color::Blue:
        return draw.count > 14;
    }
};

class Day2Solver : public LineSolver<Game>
{
public:
    Day2Solver() : LineSolver() {}

    std::string getDay() override
    {
        return "2";
    }

    Game parse(std::string line) override
    {
        return parseGame(line);
    }

    long solveItem(Game game) override
    {
        for (auto turn : game.turns)
        {
            for (auto draw : turn.colorQuantityPairs)
            {
                if (drawIsInvalid(draw))
                {
                    return 0;
                }
            }
        }
        return game.gameID;
    }

    long solveItem2(Game item) override
    {
        std::map<Color, int> colorCounts;
        colorCounts[Color::Red] = 0;
        colorCounts[Color::Green] = 0;
        colorCounts[Color::Blue] = 0;

        int redMax = 0, greenMax = 0, blueMax = 0;
        for (auto turn : item.turns)
        {
            for (auto draw : turn.colorQuantityPairs)
            {
                colorCounts[draw.color] = std::max(colorCounts[draw.color], draw.count);
            }
        }
        return colorCounts[Color::Red] * colorCounts[Color::Green] * colorCounts[Color::Blue];
    }

    long combine(std::vector<long> results) override
    {
        return std::accumulate(results.begin(), results.end(), 0);
    }
};

#endif