#include <gtest/gtest.h>

#include "search.hpp"


class SearchTest : public testing::Test {
protected:
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
};

TEST_F(SearchTest, Binary) {
    EXPECT_EQ(search::binary(arr, 10), 9);
    EXPECT_EQ(search::binary(arr, 2), 1);
    EXPECT_EQ(search::binary(arr, 19), 18);
}

TEST_F(SearchTest, Tree)  {
    std::vector<int> tree = {7, 3, 11, 1, 5, 9, 13, 0, 2, 4, 6, 8, 10, 12, 14};
    EXPECT_EQ(search::tree(tree, 8), 11);
}

TEST_F(SearchTest, Interpolation) {
    EXPECT_EQ(search::interpolation(arr, 10), 9);
    EXPECT_EQ(search::interpolation(arr, 2), 1);
    EXPECT_EQ(search::interpolation(arr, 19), 18);
}