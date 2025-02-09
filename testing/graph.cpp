#include <gtest/gtest.h>

#include "graph.hpp"

TEST(GraphTest, InsertionAndDeletion) {
    Graph<int> g;
    g.add_node(1);
    EXPECT_THROW(g.weight(1, 2);, NonexistentNode);
    g.add_node(2);
    EXPECT_THROW(g.weight(1, 2);, NonexistentEdge);
    g.set_edge(1, 2, 5);
    EXPECT_DOUBLE_EQ(g.weight(1, 2), 5);
    g.set_edge(3, 4, 27.4); // shouldn't throw anything

    std::vector<int> expected_nodes = { 1, 2, 3, 4 };
    std::vector<int> actual_nodes = g.nodes();
    std::sort(actual_nodes.begin(), actual_nodes.end());
    EXPECT_EQ(expected_nodes, actual_nodes);

    std::vector<std::tuple<int, int, double>> expected_edges = { { 1, 2, 5 }, { 3, 4, 27.4 } };
    std::vector<std::tuple<int, int, double>> actual_edges = g.edges();
    std::sort(actual_edges.begin(), actual_edges.end());
    EXPECT_EQ(expected_edges, actual_edges);
}
