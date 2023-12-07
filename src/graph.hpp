#ifndef GRAPH_H
#define GRAPH_H

template <typename T>
class DirectedGraph
{
    std::map<int, T> nodes;
    std::map<int, std::make_pair<int, int>> weights;
    std::map<int, std::vector<int>> adjacencyList;

public:
    void addNode(int id, T node)
    {
        nodes[id] = node;
    }

    void addEdge(int from, int to, int weight)
    {
        if (nodes[from] == NULL)
            throw std::runtime_error("Node " + from + " does not exist");
        if (nodes[to] == NULL)
            throw std::runtime_error("Node " + to + " does not exist");
        weights[std::make_pair(from, to)] = weight;
        adjacencyList[from].push_back(to);
    }

    T getNode(int id)
    {
        return nodes[id];
    }

    std::vector<int> getNeighbors(int id)
    {
        return adjacencyList[id];
    }

    int getWeight(int from, int to)
    {
        return weights[std::make_pair(from, to)];
    }

    std::vector<int> topologicalSort()
    {
        std::vector<int> sorted;
        std::set<int> visited;
        for (auto node : nodes)
        {
            topologicalSortUtil(node.first, visited, sorted);
        }
        return sorted;
    }

private:
    void topologicalSortUtil(int id, std::set<int> &visited, std::vector<int> &sorted)
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

template <typename T>
class UndirectedGraph : public DirectedGraph<T>
{
public:
    void addEdge(int from, int to, int weight)
    {
        DirectedGraph::addEdge(from, to, weight);
        DirectedGraph::addEdge(to, from, weight);
    }
}

#endif // End Graph