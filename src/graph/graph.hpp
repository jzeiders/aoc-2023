#pragma once

#include <map>
#include <vector>
#include <set>

template <typename N, typename T>
class DirectedGraph
{
    std::map<N, T> nodes;
    std::map<N, std::vector<N>> adjacencyList;

public:
    void addNode(N id, T node)
    {
        nodes[id] = node;
    }

    void addEdge(N from, N to)
    {
        adjacencyList[from].push_back(to);
    }

    bool hasNode(N id)
    {
        return nodes.find(id) != nodes.end();
    }

    T getNode(N id)
    {
        return nodes[id];
    }

    std::vector<N> getNeighbors(N id)
    {
        return adjacencyList[id];
    }

    std::vector<N> topologicalSort()
    {
        std::vector<N> sorted;
        std::set<N> visited;
        for (auto node : nodes)
        {
            topologicalSortUtil(node.first, visited, sorted);
        }
        return sorted;
    }

    std::map<N, int> distances(N start)
    {
        std::map<N, int> distances;
        std::set<N> q = {start};
        while (q.size())
        {
            std::set<N> next;
            for (auto current : q)
            {
                auto neighbors = getNeighbors(current);
                for (auto neighbor : neighbors)
                {
                    if (distances.find(neighbor) == distances.end())
                    {
                        distances[neighbor] = distances[current] + 1;
                        q.insert(neighbor);
                    }
                }
            }
            q = next;
        }
        return distances;
    }

private:
    void topologicalSortUtil(N id, std::set<N> &visited, std::vector<N> &sorted)
    {
        if (visited.find(id) != visited.end())
        {
            return;
        }
        visited.insert(id);
        for (auto neighbor : adjacencyList[id])
        {
            topologicalSortUtil(neighbor, visited, sorted);
        }
        sorted.push_back(id);
    }
};

template <typename N, typename T>
class UndirectedGraph : public DirectedGraph<N, T>
{
public:
    void addEdge(N from, N to)
    {
        DirectedGraph<N, T>::addEdge(from, to);
        DirectedGraph<N, T>::addEdge(to, from);
    }
};
