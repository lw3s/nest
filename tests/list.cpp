#include <fstream>
#include <cstdlib>
#include <vector>

#include <gtest/gtest.h>

#include "list.hpp"


class LinkedListTest : public testing::Test {
protected:
    List<int> ls;
public:
    LinkedListTest() {
        for (int i = 1; i <= 20; ++i) {
            ls.pushr(i);
        }
    }
};

TEST_F(LinkedListTest, OStream) {
    std::system("touch ostream_test.txt");
    std::fstream fp("ostream_test.txt", std::fstream::in | std::fstream::app);
    ASSERT_TRUE(fp.is_open());
    fp << ls;
    fp.seekg(0);
    std::string text_version(std::istreambuf_iterator<char>(fp), (std::istreambuf_iterator<char>()));
    EXPECT_EQ(text_version, "{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}");
    fp.close();
    std::system("rm ostream_test.txt");
}

TEST_F(LinkedListTest, Conversion) {
    int static_ints[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    List<int> from_static = List(static_ints, 20);
    std::vector<int> vector_ints = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    List<int> from_vector = List(vector_ints);
    List<int> from_func = List<int>([](size_t n) -> int { return n + 1; }, 20);
    EXPECT_TRUE(ls == from_static); // EXPECT_EQ doesn't like operator== being defined within the class
    EXPECT_TRUE(ls == from_vector);
    EXPECT_TRUE(ls == from_func);
}

TEST_F(LinkedListTest, Indexing) {
    ls[17] = 3;
    EXPECT_EQ(ls[5], 6);
    EXPECT_EQ(ls[-3], 3);
}

TEST_F(LinkedListTest, Edit) {
    // Delete, insert, pop, and push like your life depends on it. Hit every possibility.
}

TEST_F(LinkedListTest, FindAndDel) {
    // find_vals(), del_vals()
}

TEST_F(LinkedListTest, ApplyAndReduce) {
    // self-explanatory
}

TEST_F(LinkedListTest, Templating) {
    // do a List<double> and List<std::string> and cherry pick some fiddling from the other tests to do with them
}