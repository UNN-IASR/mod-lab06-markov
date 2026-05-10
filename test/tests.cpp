//Copyright 2026 EnganK

#include <gtest/gtest.h>
#include <deque>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <iostream>
#include "../include/textgen.h"

TEST(BuildTableTest, SinglePrefix) {
    std::istringstream input("a b c");
    statetab table;
    build_table(input, table, 1);
    prefix pref;
    pref.push_back("a");
    EXPECT_EQ(table[pref].size(), 1);
    EXPECT_EQ(table[pref][0], "b");
}

TEST(BuildTableTest, TwoPrefixes) {
    std::istringstream input("a b c d");
    statetab table;
    build_table(input, table, 2);
    prefix pref;
    pref.push_back("a");
    pref.push_back("b");
    EXPECT_EQ(table[pref].size(), 1);
    EXPECT_EQ(table[pref][0], "c");
    pref.clear();
    pref.push_back("b");
    pref.push_back("c");
    EXPECT_EQ(table[pref].size(), 1);
    EXPECT_EQ(table[pref][0], "d");
}

TEST(BuildTableTest, MultipleSuffixes) {
    std::istringstream input("a b c a b d");
    statetab table;
    build_table(input, table, 1);
    prefix pref;
    pref.push_back("a");
    EXPECT_EQ(table[pref].size(), 2);
    EXPECT_TRUE(table[pref][0] == "b" || table[pref][1] == "b");
    EXPECT_TRUE(table[pref][0] == "b" || table[pref][1] == "b");
}

TEST(BuildTableTest, EmptyInput) {
    std::istringstream input("");
    statetab table;
    build_table(input, table, 2);
    EXPECT_TRUE(table.empty());
}

TEST(BuildTableTest, SingleWordInput) {
    std::istringstream input("hello");
    statetab table;
    build_table(input, table, 2);
    EXPECT_TRUE(table.empty());
}

TEST(GenerateTextTest, GenerateLengthFive) {
    statetab table;
    prefix p;
    p.push_back("a");
    p.push_back("b");
    table[p] = { "c" };
    p.clear();
    p.push_back("b");
    p.push_back("c");
    table[p] = { "d" };
    p.clear();
    p.push_back("c");
    p.push_back("d");
    table[p] = { "e" };
    p.clear();
    p.push_back("d");
    p.push_back("e");
    table[p] = { "f" };
    std::ostringstream capture;
    std::streambuf* oldbuf = std::cout.rdbuf();
    std::cout.rdbuf(capture.rdbuf());
    std::mt19937 gen(42);
    generate_text(table, 2, 5, gen);
    std::cout.rdbuf(oldbuf);
    std::string result = capture.str();
    EXPECT_EQ(std::count(result.begin(), result.end(), ' ') + 1, 5);
}

TEST(GenerateTextTest, GenerateWithChoice) {
    statetab table;
    prefix p;
    p.push_back("a");
    p.push_back("b");
    table[p] = { "c", "d" };
    std::ostringstream capture;
    std::streambuf* oldbuf = std::cout.rdbuf();
    std::cout.rdbuf(capture.rdbuf());
    std::mt19937 gen(0);
    generate_text(table, 2, 3, gen);
    std::cout.rdbuf(oldbuf);
    std::string result = capture.str();
    EXPECT_TRUE(result.find("a b d") != std::string::npos);
}

TEST(GenerateTextTest, NoValidPrefixes) {
    statetab table;
    std::mt19937 gen(42);
    generate_text(table, 2, 10, gen);
}

TEST(GenerateTextTest, PrefixSizeMismatch) {
    statetab table;
    prefix p;
    p.push_back("a");
    table[p] = { "b" };
    std::mt19937 gen(42);
    generate_text(table, 2, 5, gen);
}

TEST(GenerateTextTest, DeterministicOutputWithFixedSeed) {
    statetab table;
    prefix p;
    p.push_back("x");
    p.push_back("y");
    table[p] = { "z", "w" };
    p.clear();
    p.push_back("y");
    p.push_back("z");
    table[p] = { "a" };
    p.clear();
    p.push_back("y");
    p.push_back("w");
    table[p] = { "b" };

    std::ostringstream capture1, capture2;
    std::streambuf* oldbuf = std::cout.rdbuf();
    std::cout.rdbuf(capture1.rdbuf());
    std::mt19937 gen1(12345);
    generate_text(table, 2, 4, gen1);
    std::cout.rdbuf(capture2.rdbuf());
    std::mt19937 gen2(12345);
    generate_text(table, 2, 4, gen2);
    std::cout.rdbuf(oldbuf);

    EXPECT_EQ(capture1.str(), capture2.str());
}
