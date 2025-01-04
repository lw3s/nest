#include <gtest/gtest.h>

#include "graph.hpp"


TEST(GraphTest, InsertionAndDeletion) {
    Graph<int> g;
    g.clear_node(1);
    EXPECT_THROW(g.update_edge(1, 2, 5);, NonexistentNode);
    g.clear_node(2);
    EXPECT_THROW(g.weight(1, 2);, NonexistentEdge);
    g.update_edge(1, 2, 5);
    EXPECT_DOUBLE_EQ(g.weight(1, 2), 5);
}

// The rest are algorithms (Dijkstra, Prim, etc): the tests should be in this file; the algorithms should be functions (not methods) in include/graph.hpp