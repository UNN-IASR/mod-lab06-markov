// Copyright 2022 UNN-IASR
#include <stdlib.h>
#include <gtest/gtest.h>
#include <deque>
#include <map>
#include <string>
#include <vector>
#include <set>
#include "textgen.h"

TEST(GeneratorTest, PrefixSize) {
    Generator gen("");
    EXPECT_EQ(gen.getNPref(), 2);
}

TEST(GeneratorTest, MaxGenValue) {
    Generator gen("");
    EXPECT_EQ(gen.getMaxGen(), 1000);
}

TEST(GeneratorTest, EmptyInputCreatesEmptyTables) {
    Generator gen("");
    EXPECT_TRUE(gen.getStateTable().empty());
    EXPECT_TRUE(gen.getPrefixSet().empty());
}

TEST(GeneratorTest, SingleWordInput) {
    Generator gen("hello");
    auto &statetab = gen.getStateTable();
    EXPECT_EQ(statetab.size(), 0);
}

TEST(GeneratorTest, WordsInput) {
    Generator gen = Generator("Say hello world");
    auto &statetab = gen.getStateTable();
    EXPECT_EQ(statetab.size(), 1);
}

TEST(GeneratorTest, PrefixSuffixRecord) {
    typedef std::deque<std::string> prefix;
    Generator gen = Generator("the cat sat");
    auto &statetab = gen.getStateTable();
    prefix p;
    p.push_back("the");
    p.push_back("cat");
    EXPECT_EQ(statetab[p].size(), 1);
    EXPECT_EQ(statetab[p][0], "sat");
}

TEST(GeneratorTest, MultipleSuffixes) {
    Generator gen("a b c a b d");
    auto &statetab = gen.getStateTable();
    Generator::prefix p = {"a", "b"};
    EXPECT_EQ(statetab[p].size(), 2);
}

TEST(GeneratorTest, SuffixSelectionFromSingleOption) {
    Generator gen("a b c");
    auto &statetab = gen.getStateTable();
    Generator::prefix p = {"a", "b"};
    ASSERT_EQ(statetab[p].size(), 1);
    EXPECT_EQ(statetab[p][0], "c");
}

TEST(GeneratorTest, TextGeneration) {
    typedef std::deque<std::string> prefix;
    Generator gen = Generator("the cat sat");
    gen.CreateText();
    std::string result = gen.getres();
    EXPECT_NE(result.find("the"), std::string::npos);
    EXPECT_NE(result.find("cat"), std::string::npos);
    EXPECT_NE(result.find("sat"), std::string::npos);
}

TEST(GeneratorTest, HandlesNewlines) {
    Generator gen("first line\nsecond line");
    auto &statetab = gen.getStateTable();
    Generator::prefix p = {"first", "line"};
    EXPECT_EQ(statetab[p].size(), 1);
    EXPECT_EQ(statetab[p][0], "second");
}
