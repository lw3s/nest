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
    // Print to file, make sure it comes back right
}

TEST_F(LinkedListTest, Conversion) {
    // Make new lists from vectors, static arrays, lambda generator
}

TEST_F(LinkedListTest, Edit) {
    // Delete, insert, pop, and push like your life depends on it. Hit every possibility.
}

TEST_F(LinkedListTest, FindAndDel) {
    // find_vals(), del_vals()
}

TEST_F(LinkedListTest, Indexing) {
    // get values from the list and set them with the [] operator.
}

TEST_F(LinkedListTest, ApplyAndReduce) {
    // self-explanatory
}

TEST_F(LinkedListTest, Templating) {
    // do a List<double> and List<std::string> and cherry pick some fiddling from the other tests to do with them
}