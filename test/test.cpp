// Copyright 2024 Goncharova Anna
#include <string>
#include "../include/textgen.h"
#include "pch.h"

TEST(test1, Prefix) {
    Generator generator;
    std::string text = "One day Lily had a dream.";
    int prefixLength = 2;
    generator.creating_statetab(text, prefixLength);
    Generator::prefix _prefix = { "One", "day" };
    EXPECT_NE(generator.statetab.find(_prefix), generator.statetab.end());
}

TEST(test2, Prefix_Suffix) {
    Generator generator;
    std::string text = "One day Lily had a dream.";
    int prefixLength = 2;
    generator.creating_statetab(text, prefixLength);
    Generator::prefix _prefix = { "One", "day" };
    EXPECT_EQ(generator.statetab[_prefix][0], "Lily");
}
TEST(test3, OnceSuffix) {
    Generator generator;
    std::string text = "One day Lily had a dream.";
    int prefixLength = 2;
    generator.creating_statetab(text, prefixLength);
    std::string result = generator.Text_generator(1, 3);
    EXPECT_EQ(result, "One day Lily ");
}
TEST(test4, VectorSuffix) {
    Generator generator;
    std::string text =
    "one two three four five six seven eight nine ten eleven twelve";
    int prefixLength = 2;
    generator.creating_statetab(text, prefixLength);
    std::string result = generator.Text_generator(2, 302);
    EXPECT_EQ(result, "one two three four ");
}

TEST(test5, Table) {
    Generator generator;
    std::string text = "one two six 1 one two six 2 one two six 3";
    int prefixLength = 2;
    std::map < Generator::prefix, std::vector < std::string >> Statetab = {
    {{"one", "two"}, {"six"}},
    {{"two", "six"}, {"1", "2", "3"}},
    {{"six", "1"}, {"one"}},
    {{"1", "one"}, {"two"}}
    };
    generator.trainFromStateTable(Statetab);
    std::string result = generator.Text_generator(2, 302);
    EXPECT_EQ(result, "1 one two six ");
}
