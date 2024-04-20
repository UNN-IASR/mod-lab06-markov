// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"

TEST(test1, FormPrefix) {
    std::vector<std::string>words{ "1", "2", "3", "4", "5" };
    MarkovChain mark;
    std::deque<std::string> prefix;
    prefix.push_back("1");
    prefix.push_back("2");
    mark.Tab(words, 2);
    EXPECT_EQ(prefix, mark.fpref);
}

TEST(test2, FormPrefixSuffix) {
    std::vector<std::string>words{ "1", "2", "3", "4", "5" };
    MarkovChain mark;
    std::deque<std::string> prefix{ "1", "2" };
    mark.Tab(words, 2);
    std::vector<std::string> suffix{ "3" };
    EXPECT_EQ(mark.statetab.begin()->second, suffix);
}

TEST(test3, ChooseSuffix) {
    std::vector<std::string>words{ "1", "2", "3", "4", "5" };
    MarkovChain mark;
    mark.Tab(words, 1);
    EXPECT_EQ(mark.CreateText(10, 10), "1 2 3 4 5 ");
}

TEST(test4, ChooseSuffixMnogo) {
    std::vector<std::string>words{ "1",
    "2", "3", "4", "5",
    "2", "3", "1", "2", "4", "5", "1"};
    MarkovChain mark;
    mark.Tab(words, 1);
    EXPECT_EQ(mark.CreateText(10, 10), "1 2 4 5 2 4 5 1 2 3 ");
}

TEST(test5, FormText) {
    typedef std::deque<std::string> prefix;
    std::map<prefix, std::vector<std::string> > state = {
        { { "two" }, { "OnE", "oNe" } },
        { { "one" }, { "tWo", "TwO" } },
        { {"three"}, {"tree"} }
    };
    MarkovChain mark;
    typedef std::deque<std::string> prefix;
    prefix pre{ "one" };
    mark.statetab = state;
    mark.fpref = pre;
    EXPECT_EQ(mark.CreateText(10, 10), "one TwO ");
}
