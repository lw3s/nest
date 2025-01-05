#include <gtest/gtest.h>

#include "sort.hpp"

class SortTest : public testing::Test {
protected:
    std::vector<int> sorted = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    std::vector<int> unsorted = {4, 17, 1, 0, 5, 8, 11, 2, 3, 10, 12, 16, 19, 13, 9, 18, 6, 7, 15, 14};
public:
    void TearDown() override {
        ASSERT_EQ(sorted, unsorted);
    }
};

TEST_F(SortTest, Radix) {
    sort::radix(unsorted);
}

TEST_F(SortTest, Shell) {
    sort::shell(unsorted);
}

TEST_F(SortTest, Quick) {
    sort::quick(unsorted);
}

TEST_F(SortTest, Tim) {
    sort::tim(unsorted);
}