#include <gtest/gtest.h>

#include "trie.hpp"
#include "euclid.hpp"

TEST(MiscellaneousTest, Trie) {
    Trie t;
    t.add("apple");
    t.add("I");
    t.add("it");
    t.add("iS");
    t.add("island");
    t.add("itinerary");
    EXPECT_TRUE(t.contains("i"));
    EXPECT_TRUE(t.contains("is"));
    EXPECT_FALSE(t.contains("isla"));
    EXPECT_TRUE(t.contains("apple"));
    EXPECT_FALSE(t.contains("a"));
    std::vector<std::string> expected_strs = {"apple", "island", "is", "itinerary", "it", "i"};
    EXPECT_EQ(t.all_strings(), expected_strs);
}

TEST(MiscellaneousTest, Euclidean) {
    EXPECT_EQ(gcf(3, 5), 1);
    EXPECT_EQ(gcf(12, 20), 4);
    EXPECT_EQ(lcm(12, 20), 60);
}