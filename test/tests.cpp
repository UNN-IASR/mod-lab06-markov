// Copyright 2026 Belev Timur

#include <gtest/gtest.h>
#include <fstream>
#include <random>
#include <string>
#include <deque>
#include <set>
#include "textgen.h"

static void writeTempFile(const std::string& content, const std::string& filename = "temp_test.txt") {
    std::ofstream f(filename);
    f << content;
    f.close();
}

TEST(TextGen, CorrectNumberOfWords) {
    TextGenerator gen(3, 10);
    writeTempFile("a b c d e f");
    gen.loadText("temp_test.txt");
    std::string result = gen.generate();
    std::deque<std::string> words;
    std::stringstream ss(result);
    std::string w;
    for (int i = 0; i < 3 && ss >> w; ++i) words.push_back(w);
    EXPECT_EQ(words.size(), 3);
    EXPECT_TRUE(gen.hasPrefix(words));
    std::remove("temp_test.txt");
}

TEST(TextGen, SingleMapping) {
    TextGenerator gen(2, 10);
    std::deque<std::string> prefix = {"hello", "world"};
    gen.addSuffix(prefix, "test");
    auto suffixes = gen.getSuffixes(prefix);
    ASSERT_EQ(suffixes.size(), 1);
    EXPECT_EQ(suffixes[0], "test");
}

TEST(TextGen, SingleSuffix) {
    TextGenerator gen(2, 5);
    std::deque<std::string> prefix = {"foo", "bar"};
    gen.addSuffix(prefix, "baz");
    for (int i = 0; i < 10; ++i) {
        std::string result = gen.generateFromPrefix(prefix);
        EXPECT_EQ(result.substr(0, 11), "foo bar baz");
    }
}

TEST(TextGen, MultipleSuffixesRandom) {
    TextGenerator gen(2, 10);
    std::deque<std::string> prefix = {"color", "is"};
    gen.addSuffix(prefix, "red");
    gen.addSuffix(prefix, "green");
    gen.addSuffix(prefix, "blue");
    std::set<std::string> seen;
    for (int i = 0; i < 50; ++i) {
        std::string result = gen.generateFromPrefix(prefix);
        std::stringstream ss(result);
        std::string w1, w2, suffix;
        ss >> w1 >> w2 >> suffix;
        if (!suffix.empty()) seen.insert(suffix);
        if (seen.size() == 3) break;
    }
    EXPECT_EQ(seen.size(), 3);
}

TEST(TextGen, FixedLengthFromManualTable) {
    TextGenerator gen(2, 5);
    std::deque<std::string> p1 = {"I", "like"};
    std::deque<std::string> p2 = {"like", "to"};
    std::deque<std::string> p3 = {"to", "eat"};
    std::deque<std::string> p4 = {"eat", "apples"};
    gen.addSuffix(p1, "to");
    gen.addSuffix(p2, "eat");
    gen.addSuffix(p3, "apples");
    gen.addSuffix(p4, ".");
    std::string result = gen.generateFromPrefix(p1);
    std::stringstream ss(result);
    int wordCount = 0;
    std::string word;
    while (ss >> word) ++wordCount;
    EXPECT_GE(wordCount, 5);
    EXPECT_LE(wordCount, 7);
}

TEST(TextGen, TextShorterThanPrefix) {
    TextGenerator gen(3, 10);
    writeTempFile("only two words");
    EXPECT_THROW(gen.loadText("temp_test.txt"), std::runtime_error);
    std::remove("temp_test.txt");
}

TEST(TextGen, NoInfiniteLoop) {
    TextGenerator gen(1, 100);
    std::deque<std::string> a = {"a"};
    std::deque<std::string> b = {"b"};
    gen.addSuffix(a, "b");
    gen.addSuffix(b, "a");
    std::string result = gen.generateFromPrefix(a);
    std::stringstream ss(result);
    int cnt = 0;
    std::string w;
    while (ss >> w) ++cnt;
    EXPECT_LE(cnt, 1 + 100);
}

TEST(TextGen, DistributionOfSuffixes) {
    TextGenerator gen(2, 100);
    std::deque<std::string> prefix = {"A", "B"};
    gen.addSuffix(prefix, "X");
    gen.addSuffix(prefix, "Y");
    int countX = 0, countY = 0;
    const int trials = 200;
    for (int i = 0; i < trials; ++i) {
        std::string result = gen.generateFromPrefix(prefix);
        if (result.find("X") != std::string::npos) ++countX;
        else if (result.find("Y") != std::string::npos) ++countY;
    }
    EXPECT_GT(countX, 10);
    EXPECT_GT(countY, 10);
}

TEST(TextGen, MaxWordLimit) {
    TextGenerator gen(2, 5);
    writeTempFile("one two three four five six seven eight nine ten");
    gen.loadText("temp_test.txt");
    std::string result = gen.generate();
    std::stringstream ss(result);
    int wordCount = 0;
    std::string w;
    while (ss >> w) ++wordCount;
    EXPECT_LE(wordCount, 2 + 5);
    std::remove("temp_test.txt");
}

TEST(TextGen, ClearTableResets) {
    TextGenerator gen(2, 10);
    std::deque<std::string> prefix = {"test", "prefix"};
    gen.addSuffix(prefix, "suffix");
    EXPECT_TRUE(gen.hasPrefix(prefix));
    gen.clearTable();
    EXPECT_FALSE(gen.hasPrefix(prefix));
    EXPECT_EQ(gen.getTableSize(), 0);
}

TEST(TextGen, GenerateFromUnknownPrefix) {
    TextGenerator gen(2, 10);
    std::deque<std::string> unknown = {"unknown", "prefix"};
    std::string result = gen.generateFromPrefix(unknown);
    EXPECT_TRUE(result.empty());
}
