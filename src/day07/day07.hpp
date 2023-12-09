#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <compare>

#include "solver.hpp"

class Hand
{
public:
    bool promoteJ;
    std::vector<int> cards;
    int type() const;
    Hand(std::vector<int> cards) : cards(cards) {}
};

bool operator==(const Hand &lhs, const Hand &rhs);

std::strong_ordering operator<=>(const Hand &lhs, const Hand &rhs);

using Line = std::pair<Hand, int>;

class Day7Solver : public LineSolver<Line, Line>
{
public:
    std::string getDay() override;
    Line parse(std::string line) override;
    Line solveItem(Line line) override;
    Line solveItem2(Line line) override;
    long combine(std::vector<Line> results) override;
};