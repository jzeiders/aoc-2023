#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

inline std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

// Print any iterable container
template <typename T>
void print(const T &container)
{
    for (auto &item : container)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

inline int sumVector(const std::vector<int> &numbers)
{
    return std::accumulate(numbers.begin(), numbers.end(), 0);
}

#endif // COMMON_HPP