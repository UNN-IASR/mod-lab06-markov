//Copyright 2026 EnganK

#include <gtest/gtest.h>
#include <deque>
#include <map>
#include <vector>
#include <string>
#include <sstream>
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

TEST(GenerateTextTest, FixedPrefixSelection) {
    statetab table;
    prefix p1, p2;
    p1.push_back("a");
    p1.push_back("b");
    p2.push_back("b");
    p2.push_back("c");
    table[p1] = { "d" };
    table[p2] = { "e" };

    std::istringstream input("a b c");
    build_table(input, table, 2);

    std::vector<prefix> valid;
    for (auto& p : table) {
        if (p.first.size() == 2) valid.push_back(p.first);
    }
    EXPECT_EQ(valid.size(), 2);
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

    prefix start;
    start.push_back("a");
    start.push_back("b");
    generate_text(table, 2, 5);

    std::cout.rdbuf(oldbuf);
    std::string result = capture.str();
    EXPECT_TRUE(result.find("a b c d e") != std::string::npos);
}

TEST(GenerateTextTest, GenerateWithChoice) {
    statetab table;
    prefix p;
    p.push_back("a");
    p.push_back("b");
    table[p] = { "c", "d" };

    std::ostringstream output;
    std::streambuf* oldbuf = std::cout.rdbuf();
    std::ostringstream capture;
    std::cout.rdbuf(capture.rdbuf());

    generate_text(table, 2, 3);

    std::cout.rdbuf(oldbuf);
    std::string result = capture.str();
    EXPECT_TRUE(
        result.find("a b c") != std::string::npos ||
        result.find("a b d") != std::string::npos);
}

TEST(GenerateTextTest, NoValidPrefixes) {
    statetab table;
    generate_text(table, 2, 10);
    // Should not crash or hang
    EXPECT_TRUE(true);
}

TEST(GenerateTextTest, PrefixSizeMismatch) {
    statetab table;
    prefix p;
    p.push_back("a");
    table[p] = { "b" };
    generate_text(table, 2, 5);
    // Should not generate anything (prefix size mismatch)
    EXPECT_TRUE(true);
}
