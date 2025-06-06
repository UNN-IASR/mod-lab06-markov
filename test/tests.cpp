// Copyright 2025 cherniuta
#include <gtest/gtest.h>
#include <deque>
#include <string>
#include "../include/textgen.h"

TEST(TextGenTest, PrefixFormation) {
    TextGen gen(2);
    std::deque<std::string> prefix = {"word1", "word2"};
    gen.add(prefix, "suffix1");
    EXPECT_EQ(gen.get_random_suffix(prefix), "suffix1");
}

TEST(TextGenTest, SingleSuffix) {
    TextGen gen(2);
    std::deque<std::string> prefix = {"test", "prefix"};
    gen.add(prefix, "only_suffix");
    EXPECT_EQ(gen.get_random_suffix(prefix), "only_suffix");
}

TEST(TextGenTest, MultipleSuffixes) {
    TextGen gen(2);
    std::deque<std::string> prefix = {"multiple", "suffixes"};
    gen.add(prefix, "suffix1");
    gen.add(prefix, "suffix2");
    gen.add(prefix, "suffix3");

    std::string suffix = gen.get_random_suffix(prefix);
    EXPECT_TRUE(suffix == "suffix1" || suffix == "suffix2" ||
                suffix == "suffix3");
}

TEST(TextGenTest, EmptyState) {
    TextGen gen(2);
    std::deque<std::string> prefix = {"empty", "state"};
    EXPECT_TRUE(gen.get_random_suffix(prefix).empty());
}

TEST(TextGenTest, TextGeneration) {
    TextGen gen(2);
    std::deque<std::string> prefix1 = {"start", "with"};
    std::deque<std::string> prefix2 = {"with", "this"};
    std::deque<std::string> prefix3 = {"this", "text"};

    gen.add(prefix1, "this");
    gen.add(prefix2, "text");
    gen.add(prefix3, "end");

    std::string result = gen.generate(5);
    EXPECT_FALSE(result.empty());
}

TEST(TextGenTest, PrefixSize) {
    TextGen gen(3);
    std::deque<std::string> prefix = {"three", "word", "prefix"};
    gen.add(prefix, "suffix");
    EXPECT_EQ(gen.get_random_suffix(prefix), "suffix");
}

TEST(TextGenTest, WordBoundaries) {
    TextGen gen(2);
    std::deque<std::string> prefix = {"word", "with"};
    gen.add(prefix, "spaces");
    std::string result = gen.generate(3);
    EXPECT_EQ(result.find("  "), std::string::npos);
}

TEST(TextGenTest, EmptyGeneration) {
    TextGen gen(2);
    std::string result = gen.generate(10);
    EXPECT_TRUE(result.empty());
}

TEST(TextGenTest, SingleWordPrefix) {
    TextGen gen(1);
    std::deque<std::string> prefix = {"single"};
    gen.add(prefix, "word");
    EXPECT_EQ(gen.get_random_suffix(prefix), "word");
}

TEST(TextGenTest, LargeGeneration) {
    TextGen gen(2);
    std::deque<std::string> prefix = {"start", "sequence"};
    gen.add(prefix, "continues");
    std::string result = gen.generate(1000);
    EXPECT_GT(result.length(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
