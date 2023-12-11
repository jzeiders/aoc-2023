#include <gtest/gtest.h>

#include "graph/graph.hpp"

TEST(DisntanceTest, Default)
{
    auto graph = UndirectedGraph<int, int>();
    graph.addNode(1, 1);
    graph.addNode(2, 2);
    graph.addNode(3, 3);

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);

    auto distances = graph.distances(1);

    EXPECT_EQ(distances[1], 0);
    EXPECT_EQ(distances[2], 1);
    EXPECT_EQ(distances[3], 2);

    auto distances2 = graph.distances(2);

    EXPECT_EQ(distances2[1], 1);
    EXPECT_EQ(distances2[2], 0);
    EXPECT_EQ(distances2[3], 1);
}