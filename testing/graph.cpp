#include <gtest/gtest.h>

#include "graph.hpp"

std::vector<int> sort(std::vector<int> arr) { // quick-and-dirty selection sort; will change once we get sorting algorithms implemented
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = i; j < arr.size(); ++j) {
            if (arr[j] < arr[i]) {
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
    return arr;
}

TEST(GraphTest, InsertionAndDeletion) {
    Graph<int> g;
    g.clear_node(1);
    EXPECT_THROW(g.update_edge(1, 2, 5);, NonexistentNode);
    g.clear_node(2);
    EXPECT_THROW(g.weight(1, 2);, NonexistentEdge);
    g.update_edge(1, 2, 5);
    EXPECT_DOUBLE_EQ(g.weight(1, 2), 5);
    EXPECT_EQ(sort(g.nodes()), sort({1, 2}));
    std::vector<std::tuple<int, int, double>> expected_edges = {{1, 2, 5}};
    EXPECT_EQ(g.edges(), expected_edges);
}

// The rest are algorithms (Dijkstra, Prim, etc): the tests should be in this file; the algorithms should be functions in include/graph.hpp