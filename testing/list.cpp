#include <fstream>
#include <cstdlib>
#include <vector>
#include <iostream>

#include <gtest/gtest.h>

#include "list.hpp"

class LinkedListTest : public testing::Test {
protected:
    List<int> ls = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
};

TEST_F(LinkedListTest, Conversion) {
    int static_ints[20] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    List<int> from_static = List(static_ints, 20);
    std::vector<int> vector_ints = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    List<int> from_vector = List(vector_ints);
    List<int> from_func = List<int>([](int n) -> int { return n + 1; }, 20);
    EXPECT_TRUE(ls == from_static); // EXPECT_EQ doesn't like operator== being defined within the class
    EXPECT_TRUE(ls == from_vector);
    EXPECT_TRUE(ls == from_func);
}

TEST_F(LinkedListTest, Indexing) {
    ls[17] = 3;
    EXPECT_EQ(ls[5], 6);
    EXPECT_EQ(ls[-3], 3);
}

TEST_F(LinkedListTest, Edit) { // Lots of moving parts here, I want path coverage.
    ls.popl();
    ls.popr();
    ls.pushl(20);
    ls.pushr(1);
    ls.insert(2, 5);
    ls.insert(-17, 23);
    ls.insert(18, 43);
    ls.insert(-4, 22);
    ls.del(1);
    ls.del(16);
    ls.del(-2);
    ls.del(-18);
    EXPECT_EQ(ls.string(), "{ 20, 5, 3, 23, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 43, 17, 22, 18, 1 }");
}

TEST_F(LinkedListTest, FindAndDel) {
    List<int> newls([](int n) -> int { return (n + 1) % 4; }, 20);
    EXPECT_EQ(newls.find_vals(3), std::vector<int>({2, 6, 10, 14, 18}));
    newls.del_vals(2);
    EXPECT_EQ(newls.string(), "{ 1, 3, 0, 1, 3, 0, 1, 3, 0, 1, 3, 0, 1, 3, 0 }");
}

TEST_F(LinkedListTest, ApplyAndReduce) {
    for (int _ = 0; _ < 10; ++_) ls.popr();
    EXPECT_EQ(ls.reduce([](int a, int b) -> int { return a + b; }), 55);
    EXPECT_EQ(ls.reduce([](int a, int b) -> int { return a * b; }), 0);
    EXPECT_EQ(ls.reduce([](int a, int b) -> int { return a * b; }, 1), 3628800);
    ls.apply([](int n) -> int { return n * n; });
    EXPECT_EQ(ls.string(), "{ 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 }");
}
