// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "textgen.h"

static const int NPREF = 2;

TEST(MarkovTests, BuildPrefixMap_FewerWords) {
    std::istringstream in("one two");
    statetab_t tab;
    build_prefix_map(in, tab, NPREF);
    EXPECT_TRUE(tab.empty());
}

TEST(MarkovTests, BuildPrefixMap_RecordSuffix) {
    std::istringstream in("a b c d");
    statetab_t tab;
    build_prefix_map(in, tab, NPREF);
    prefix key = {"a","b"};
    ASSERT_NE(tab.find(key), tab.end());
    EXPECT_EQ(1u, tab[key].size());
    EXPECT_EQ("c", tab[key][0]);
}

TEST(MarkovTests, GenerateText_SingleSuffix) {
    statetab_t tab;
    prefix p = {"x","y"};
    tab[p] = {"z"};
    std::srand(1);
    auto words = generate_text(tab, 2, 5);
    EXPECT_EQ(7u, words.size());  // 2 initial + 5 generated
    for (size_t i = 2; i < words.size(); ++i) {
        EXPECT_EQ("z", words[i]);
    }
}

TEST(MarkovTests, GenerateText_MultipleSuffixes) {
    statetab_t tab;
    prefix p = {"m","n"};
    tab[p] = {"z","w","v"};
    std::srand(2);
    auto words = generate_text(tab, 2, 6);
    ASSERT_EQ(8u, words.size());
    EXPECT_TRUE(words[2] == "z" || words[2] == "w" || words[2] == "v");
    EXPECT_TRUE(words[3] == "z" || words[3] == "w" || words[3] == "v");
}

TEST(MarkovTests, GenerateText_Length) {
    statetab_t tab;
    prefix p = {"a","b"};
    tab[p] = {"c"};
    std::srand(4);
    auto words = generate_text(tab, 2, 0);
    EXPECT_TRUE(words.size() >= 2);
}

TEST(MarkovTests, GenerateText_EmptyStatetab) {
    statetab_t tab;
    std::srand(5);
    auto words = generate_text(tab, 2, 10);
    EXPECT_TRUE(words.empty());
}

TEST(MarkovTests, GenerateText_NegativeMaxgen) {
    statetab_t tab;
    prefix p = {"a","b"};
    tab[p] = {"c"};
    std::srand(6);
    auto words = generate_text(tab, 2, -5);
    EXPECT_TRUE(words.empty());
}

TEST(MarkovTests, BuildPrefixMap_PrefLargerThanWords) {
    std::istringstream in("one");
    statetab_t tab;
    build_prefix_map(in, tab, 3);
    EXPECT_TRUE(tab.empty());
}

TEST(MarkovTests, GenerateText_ManualStatetab) {
    statetab_t tab;
    prefix p = {"p","q"};
    tab[p] = {"r","s"};
    std::srand(7);
    auto words = generate_text(tab, 2, 4);
    EXPECT_EQ(6u, words.size());
}

TEST(MarkovTests, GenerateText_RestartOnDeadEnd) {
    statetab_t tab;
    prefix p1 = {"a","b"};
    prefix p2 = {"c","d"};
    tab[p1] = {"x"};
    tab[p2] = {};
    std::srand(3);
    auto words = generate_text(tab, 2, 6);
    EXPECT_EQ(6u, words.size());
}
