
#include "solver.hpp"
#include "day07/day07.hpp"
#include "common/common.hpp"
#include <algorithm>
#include <compare>

int Hand::type() const
{

    auto grouped = groupBy(cards, [](int card)
                           { return card; });
    if (promoteJ)
    {
        grouped.erase(11);
    }

    std::vector<int> setSizes;
    std::transform(grouped.begin(), grouped.end(), std::back_inserter(setSizes), [](auto &pair)
                   { return pair.second.size(); });

    std::sort(setSizes.begin(), setSizes.end(), std::greater<int>());

    if (promoteJ)
    {
        auto jCount = std::count(cards.begin(), cards.end(), 11);
        if (jCount == 5)
        {
            if (setSizes.size() != 0)
            {
                throw std::runtime_error("Invalid hand");
            }
            return 7;
        }
        setSizes[0] += jCount;
    }

    // All cards the same
    if (setSizes == std::vector<int>{5})
        return 7;
    if (setSizes == std::vector<int>{4, 1})
        return 6;
    if (setSizes == std::vector<int>{3, 2})
        return 5;
    if (setSizes == std::vector<int>{3, 1, 1})
        return 4;
    if (setSizes == std::vector<int>{2, 2, 1})
        return 3;
    if (setSizes == std::vector<int>{2, 1, 1, 1})
        return 2;
    if (setSizes == std::vector<int>{1, 1, 1, 1, 1})
        return 1;
    print(cards);
    throw std::runtime_error("Invalid hand");
}

bool operator==(const Hand &lhs, const Hand &rhs)
{
    return lhs.cards == rhs.cards;
}

std::strong_ordering operator<=>(const Hand &lhs, const Hand &rhs)
{
    if (lhs.type() < rhs.type())
        return std::strong_ordering::less;
    if (lhs.type() > rhs.type())
        return std::strong_ordering::greater;
    return lhs.cards <=> rhs.cards;
};

using Line = std::pair<Hand, int>;

std::string Day7Solver::getDay() { return "7"; }

Line Day7Solver::parse(std::string line)
{
    std::istringstream lineStream(line);
    std::string cardRaw;
    int value;
    lineStream >> cardRaw >> value;

    std::vector<int> cards;
    for (auto &s : cardRaw)
    {
        switch (s)
        {
        case 'A':
            cards.push_back(14);
            break;
        case 'K':
            cards.push_back(13);
            break;
        case 'Q':
            cards.push_back(12);
            break;
        case 'J':
            cards.push_back(11);
            break;
        case 'T':
            cards.push_back(10);
            break;
        default:
            cards.push_back(s - '0');
        }
    }
    return std::make_pair(Hand(cards), value);
}

Line Day7Solver::solveItem(Line line)
{
    return line;
}
Line Day7Solver::solveItem2(Line line)
{
    line.first.promoteJ = true;
    return line;
}

long Day7Solver::combine(std::vector<Line> results)
{

    std::sort(results.begin(), results.end(), [](Line &a, Line &b)
              { return a.first < b.first; });
    long result = 0;

    for (int i = 0; i < results.size(); i++)
    {
        if (i >= 1)
        {
            if (results[i].first < results[i - 1].first)
            {
                throw std::runtime_error("Invalid input");
            }
        }
        result += results[i].second * (i + 1);
    }
    return result;
}