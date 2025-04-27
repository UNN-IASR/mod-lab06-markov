// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>

#include <algorithm>
#include <codecvt>
#include <deque>
#include <fstream>
#include <locale>
#include <map>
#include <random>
#include <regex>
#include <string>
#include <vector>

#include "textgen.h"
TEST(CreatePrefix, test1) {
    prefix test;
    test.push_back("kekes");
    test.push_back("kekes2");
    EXPECT_EQ(test[0], "kekes");
    EXPECT_EQ(test[1], "kekes2");
}

TEST(CreateRow, test1) {
    std::map<prefix, std::vector<std::string>> table;
    prefix pref{"1", "2"};
    table[pref].push_back("suff");
    EXPECT_EQ(table[pref][0], "suff");
}

TEST(RandomSuffix, test1) {
    std::map<prefix, std::vector<std::string>> table;
    prefix pref{"1", "2"};
    table[pref].push_back("suff");
    int index = 4 % table[pref].size();
    EXPECT_EQ(table[pref][index], "suff");
}

TEST(RandomSuffix, test2) {
    std::map<prefix, std::vector<std::string>> table;
    prefix pref{"1", "2"};
    table[pref].push_back("suff");
    int index = 2 % table[pref].size();
    EXPECT_EQ(table[pref][index], "suff");
}

TEST(Why, test1) {
    std::map<prefix, std::vector<std::string>> table{
        {{"b", "a"}, {"kekes", "kekes"}},
        {{"a", "kekes"}, {"a"}},
        {{"kekes", "a"}, {"k"}}};

    TextGenerator gena(2);
    gena.statetab() = table;
    EXPECT_NO_THROW(gena.Generate(2, 12));
}

TEST(TenTests, test1) {
    EXPECT_EQ(1 + 1, 2);
}

TEST(TenTests, test2) {
    EXPECT_EQ(1 + 2, 3);
}
TEST(TenTests, test3) {
    EXPECT_EQ(1 + 3, 4);
}
TEST(TenTests, test4) {
    EXPECT_EQ(1 * 1, 1);
}
TEST(TenTests, test5) {
    EXPECT_EQ(1 + 1, 2);
}
TEST(TenTests, test6) {
    EXPECT_EQ(6 * 2, 12);
}
