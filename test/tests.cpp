// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"

TEST(test1, 1Test) {
    Markov mark;
    std::vector<std::string>words{ "a", "b", "c"};
    std::deque<std::string> prefix;
    prefix.push_back("a");
    prefix.push_back("b");
    mark.CreateStatetab(words, 2);
    EXPECT_EQ(prefix, mark.firstPref);
}

TEST(test2, 2Test) {
    Markov mark;
    std::vector<std::string>words{ "a", "b", "c"};
    std::deque<std::string> prefix{ "a", "b" };
    mark.CreateStatetab(words, 2);
    std::vector<std::string> suffix{ "c" };
    EXPECT_EQ(mark.statetab.begin()->second, suffix);
}

TEST(test3, 99Test) {
    std::vector<std::string>words{ "a", "b", "3", "4", "c" };
    Markov mark;
    mark.CreateStatetab(words, 1);
    EXPECT_EQ(mark.CreateText(10), "a b 3 4 c ");
}

TEST(test4, 3Test) {
    Markov mark;
    std::vector<std::string>words{ "1",
    "2", "3", "4", "5",
    "2", "3", "1", "2", "4",
    "5", "1"};
    mark.CreateStatetab(words, 1);
    EXPECT_EQ(mark.CreateText(10), "1 2 4 5 2 4 5 2 4 5 ");
}

TEST(test5, F4Test) {
    Markov mark;
    typedef std::deque<std::string> prefix;
    std::map<prefix, std::vector<std::string> > state = {
        { { "two" }, { "OnE23", "oNe" } },
        { { "one11" }, { "tWo", "TwO1" } },
        { {"three2"}, {"tree"} }
    };
    prefix pre{ "one1" };
    mark.statetab = state;
    mark.firstPref = pre;
    EXPECT_EQ(mark.CreateText(10), "one1 ");
}
