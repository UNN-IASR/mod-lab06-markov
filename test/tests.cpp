// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <sstream>
#include "textgen.h"

static const int NPREF = 2;

TEST(MarkovTests, BuildPrefixMap_FewerWords) {
    std::istringstream in("one two");
    statetab_t tab;
    build_prefix_map(in, tab, NPREF);
    EXPECT_TRUE(tab.empty());
}

TEST(MarkovTests, BuildPrefixMap_RecordSuffix) {
    std::istringstream in("one two three four");
    statetab_t tab;
    build_prefix_map(in, tab, NPREF);
    prefix p1 = {"one", "two"};
    prefix p2 = {"two", "three"};
    EXPECT_EQ(2u, tab.size());
    ASSERT_EQ(1u, tab[p1].size());
    EXPECT_EQ("three", tab[p1][0]);
    ASSERT_EQ(1u, tab[p2].size());
    EXPECT_EQ("four", tab[p2][0]);
}

TEST(MarkovTests, GenerateText_SingleSuffix) {
    std::istringstream in("a b c");
    statetab_t tab;
    build_prefix_map(in, tab, NPREF);
    std::srand(0);
    auto words = generate_text(tab, NPREF, 5);
    EXPECT_EQ(5u, words.size());
    for (size_t i = NPREF; i < words.size(); ++i) {
        EXPECT_EQ("c", words[i]);
    }
}

TEST(MarkovTests, GenerateText_MultipleSuffixes) {
    std::istringstream in("x y z x y w x y v");
    statetab_t tab;
    build_prefix_map(in, tab, NPREF);
    std::srand(1);
    auto words = generate_text(tab, NPREF, 4);
    EXPECT_EQ(4u, words.size());
    std::string w = words[2];
    EXPECT_TRUE(w=="z" || w=="w" || w=="v");
}

TEST(MarkovTests, GenerateText_Length) {
    std::istringstream in("p q r s t u v w x y z");
    statetab_t tab;
    build_prefix_map(in, tab, NPREF);
    std::srand(2);
    auto words = generate_text(tab, NPREF, 10);
    EXPECT_EQ(10u, words.size());
}

TEST(MarkovTests, GenerateText_EmptyStatetab) {
    statetab_t tab;
    auto words = generate_text(tab, NPREF, 5);
    EXPECT_TRUE(words.empty());
}

TEST(MarkovTests, GenerateText_NegativeMaxgen) {
    std::istringstream in("a b c d");
    statetab_t tab;
    build_prefix_map(in, tab, NPREF);
    auto words = generate_text(tab, NPREF, -1);
    EXPECT_TRUE(words.empty());
}

TEST(MarkovTests, BuildPrefixMap_PrefLargerThanWords) {
    std::istringstream in("only one word");
    statetab_t tab;
    build_prefix_map(in, tab, 5);
    EXPECT_TRUE(tab.empty());
}

TEST(MarkovTests, GenerateText_ManualStatetab) {
    statetab_t tab;
    prefix p = {"m","n"};
    tab[p] = {"o"};
    std::srand(0);
    auto words = generate_text(tab, 2, 4);
    ASSERT_EQ(4u, words.size());
    EXPECT_EQ('m', words[0][0]); // starts with m
    EXPECT_EQ('n', words[1][0]);
    EXPECT_EQ("o", words[2]);
    EXPECT_EQ("o", words[3]);
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
