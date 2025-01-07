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

TEST_F(SearchTest, Bintree)  {

}

TEST_F(SearchTest, Interpolation) {

}