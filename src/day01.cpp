#ifndef DAY1_H
#define DAY1_H

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "solver.hpp"

inline std::string findFirstDigit(std::string line)
{
    size_t pos = line.find_first_of("123456789");
    return std::string(1, line[pos]);
};

inline bool isWordAtPosition(const std::string &str, const std::string &word, size_t pos)
{
    if (pos + word.length() > str.length())
    {
        return false; // Position plus word length exceeds string length
    }

    return str.substr(pos, word.length()) == word;
}

inline bool replaceWord(std::string *str, const std::string &target, const std::string &replacement)
{
    size_t pos = 0;
    if ((pos = str->find(target, pos)) != std::string::npos)
    {
        // Check if the word at the current position matches the target
        if (str->substr(pos, target.length()) == target)
        {
            str->replace(pos, target.length(), replacement);
            return true;
        }
    }
    return false;
}

class Day1Solver : public LineSolver<std::string>
{
public:
    Day1Solver() : LineSolver() {}

    std::string getDay() override
    {
        return "1";
    }

    std::string parse(std::string line) override
    {
        return line;
        // Parse to int
    }

    int solveItem(std::string item) override
    {
        std::string firstDigit = findFirstDigit(item);

        std::reverse(item.begin(), item.end());
        std::string lastDigit = findFirstDigit(item);

        // Concatenate the two digits into a string
        std::string digits;
        digits += firstDigit;
        digits += lastDigit;

        int digit = std::stoi(digits);
        return digit;
    }

    void processString(std::string &item)
    {
        auto words = std::vector<std::string>{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
        for (auto it = item.begin(); it != item.end(); ++it)
        {
            for (int i = 0; i < words.size(); i++)
            {
                if (isWordAtPosition(item, words[i], it - item.begin()))
                {
                    item.insert(it - item.begin(), std::to_string(i + 1));
                    return;
                }
            }
        }
    }

    void processStringBackwards(std::string &item)
    {
        auto words = std::vector<std::string>{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
        for (auto it = item.end(); it != item.begin(); --it)
        {
            for (int i = 0; i < words.size(); i++)
            {
                if (isWordAtPosition(item, words[i], it - item.begin()))
                {
                    item.insert(it - item.begin(), std::to_string(i + 1));
                    return;
                }
            }
        }
    }

    int solveItem2(std::string item) override
    {

        processString(item);
        processStringBackwards(item);

        return this->solveItem(item);
    }

    int combine(std::vector<int> results) override
    {
        int sum = 0;
        for (int result : results)
        {
            sum += result;
        }
        return sum;
    }
};

#endif // DAY1_H