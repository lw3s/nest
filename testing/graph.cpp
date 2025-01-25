#include <gtest/gtest.h>


#include "graph.hpp"


std::vector<int> sort(std::vector<int> arr) { // quick-and-dirty selection sort
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
    g.add_node(1);
    EXPECT_THROW(g.set_edge(1, 2, 5);, NonexistentNode);
    g.add_node(2);
    EXPECT_THROW(g.weight(1, 2);, NonexistentEdge);
    g.set_edge(1, 2, 5);
    EXPECT_DOUBLE_EQ(g.weight(1, 2), 5);
    EXPECT_EQ(sort(g.nodes()), sort({1, 2}));
    std::vector<std::tuple<int, int, double>> expected_edges = {{1, 2, 5}};
    EXPECT_EQ(g.edges(), expected_edges);
}