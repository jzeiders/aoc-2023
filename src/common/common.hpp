#pragma once

#include <iostream>
#include <vector>
#include <map>

std::vector<std::string> split(const std::string &str, char delimiter);

// Prlong ny iterable container
template <typename T>
void print(const T &container)
{
    for (auto &item : container)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

int sumVector(const std::vector<int> &numbers);

template <typename Container, typename Function>
auto groupBy(const Container &elements, Function func)
{
    using KeyType = decltype(func(*elements.begin()));
    using GroupType = std::unordered_map<KeyType, std::vector<typename Container::value_type>>;

    GroupType groupedElements;

    for (const auto &element : elements)
    {
        groupedElements[func(element)].push_back(element);
    }

    return groupedElements;
}
