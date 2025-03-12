#include <gtest/gtest.h>

#include "graph.hpp"

class GraphTest : public testing::Test {
protected:
    Graph<int> g;
public:
    void SetUp() {
        // represented in graph_image.png
        g = {
            { 0, 1, 5 },
            { 0, 2, 4 },
            { 1, 2, 6 },
            { 1, 3, 12 },
            { 2, 4, 1 },
            { 2, 8, 13 },
            { 3, 5, 3 },
            { 3, 8, 9 },
            { 4, 1, 7 },
            { 4, 6, 3 },
            { 5, 4, 4 },
            { 5, 7, 7 },
            { 6, 5, 4 },
            { 7, 6, 8 },
            { 8, 4, 7 }
        };
    }
};

TEST_F(GraphTest, InsertionAndDeletion) {
    Graph <int> g;
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

TEST_F(GraphTest, Output) {
    std::string correct_str = "7---8-->6\n6---4-->5\n5---7-->7\n5---4-->4\n8---7-->4\n4---3-->6\n4---7-->1\n3---9-->8\n3---3-->5\n2---13-->8\n2---1-->4\n1---12-->3\n1---6-->2\n0---4-->2\n0---5-->1\n";
    EXPECT_EQ((std::ostringstream() << g).str(), correct_str);
}
