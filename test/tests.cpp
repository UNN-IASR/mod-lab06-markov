// Copyright 2025 <A-Sabu>
#include <gtest/gtest.h>
#include <algorithm>
#include <deque>
#include <sstream>
#include <string>
#include "textgen.h"

TEST(MarkovTest, PrefixSizeOne) {
    Markov generator(1, 1000);
    generator.learnFromString("The agile puss in boots");
    auto table = generator.getStateTable();
    EXPECT_EQ(table.begin()->first.size(), 1);
}

TEST(MarkovTest, PrefixSizeTwo) {
    Markov generator;
    generator.learnFromString("The agile puss in boots");
    auto table = generator.getStateTable();
    EXPECT_EQ(table.begin()->first.size(), 2);
}

TEST(MarkovTest, FirstSuffix) {
    Markov generator;
    generator.learnFromString("The agile puss in boots");
    std::deque<std::string> prefix = { "The", "agile" };
    auto table = generator.getStateTable();
    ASSERT_TRUE(table.count(prefix));
    EXPECT_EQ(table[prefix][0], "puss");
}

TEST(MarkovTest, SingleSuffix) {
    Markov generator;
    generator.learnFromString("agile puss");
    std::deque<std::string> prefix = { "\n", "agile" };
    auto table = generator.getStateTable();
    ASSERT_TRUE(table.count(prefix));
    EXPECT_EQ(table[prefix][0], "puss");
}

TEST(MarkovTest, PicksAmongMultipleSuffixes) {
    Markov generator(1, 1000);
    generator.learnFromString("agile puss sly puss");
    std::deque<std::string> prefix = { "agile" };
    auto table = generator.getStateTable();
    ASSERT_TRUE(table.count(prefix));
    auto suffixes = table[prefix];
    EXPECT_TRUE(
        std::find(suffixes.begin(), suffixes.end(), "puss") != suffixes.end() ||
        std::find(suffixes.begin(), suffixes.end(), "sly") != suffixes.end());
}


TEST(MarkovTest, GenerateTextOfFixedLength) {
    Markov generator(2, 7);
    generator.learnFromString("He was sly and agile puss in boots.");
    generator.generateText();
    std::string output = generator.getGeneratedText();
    std::istringstream iss(output);
    int wordCount = 0;
    std::string word;
    while (iss >> word) ++wordCount;
    EXPECT_EQ(wordCount, 7);
}

TEST(MarkovTest, EmptyInputResultsInEmptyMap) {
    Markov generator;
    generator.learnFromString("");
    int actual = generator.getStateTable().size();
    EXPECT_EQ(actual, 1);
}

TEST(MarkovTest, GeneratedStringNotEmpty) {
    Markov generator;
    generator.learnFromString("The agile puss in boots");
    generator.generateText();
    EXPECT_FALSE(generator.getGeneratedText().empty());
}

TEST(MarkovTest, PrefixSuffixMappingExists) {
    Markov generator;
    generator.learnFromString("Puss in boots");
    auto table = generator.getStateTable();
    std::deque<std::string> prefix = { "Puss", "in" };
    ASSERT_TRUE(table.count(prefix));
    EXPECT_EQ(table[prefix][0], "boots");
}

TEST(MarkovTest, PicksSingleSuffixCorrectly) {
    Markov generator(1, 1000);
    generator.learnFromString("Puss");
    std::deque<std::string> prefix = { "\n" };
    auto table = generator.getStateTable();
    ASSERT_TRUE(table.count(prefix));
    const auto& suffixes = table[prefix];
    ASSERT_EQ(suffixes.size(), 1);
    EXPECT_EQ(suffixes[0], "Puss");
}

TEST(MarkovTest, LearningTwiceChangesTable) {
    Markov generator;
    generator.learnFromString("The agile puss in boots");
    int size1 = generator.getStateTable().size();
    generator.learnFromString("The elusive goose");
    int size2 = generator.getStateTable().size();
    EXPECT_NE(size1, size2);
}
