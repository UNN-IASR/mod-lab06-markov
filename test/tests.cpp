// Copyright 2021 GHA Test Team
#include <textgen.h>
#include <map>
#include <string>
#include <vector>
#include <gtest/gtest.h>

TEST(PrefixTests, NormalPrefixCreation) {
    std::vector<std::string> words = {"A", "B", "С", "D"};
    TextGeneratorClass tg("");
    auto stateTab = tg.buildStateTab(words);
    prefix expected = {"A", "B"};
    ASSERT_EQ(tg.GetStartPrefix(), expected);
}

TEST(PrefixTests, InsufficientWordsForPrefix) {
    std::vector<std::string> words = {"SingleWord"};
    TextGeneratorClass tg("");
    auto stateTab = tg.buildStateTab(words);
    ASSERT_TRUE(stateTab.empty());
}

TEST(StateTableTests, SingleSuffixEntry) {
    std::vector<std::string> words = {"A", "B", "C"};
    TextGeneratorClass generator("");
    auto stateTab = generator.buildStateTab(words);
    prefix key = {"A", "B"};
    std::vector<std::string> expected = {"C"};
    ASSERT_EQ(stateTab[key], expected);
}

TEST(StateTableTests, MultipleSuffixes) {
    std::vector<std::string> words = {"A", "B", "C", "A", "B", "D"};
    TextGeneratorClass generator("");
    auto stateTab = generator.buildStateTab(words);
    prefix key = {"A", "B"};
    std::vector<std::string> expected = {"C", "D"};
    ASSERT_EQ(stateTab[key], expected);
}

TEST(StateTableTests, OverlappingPrefixes) {
    std::vector<std::string> words = {"A", "B", "B", "A", "B"};
    TextGeneratorClass generator("");
    auto stateTab = generator.buildStateTab(words);
    prefix key1 = {"A", "B"};
    prefix key2 = {"B", "B"};
    prefix key3 = {"B", "A"};
    std::vector<std::string> exp1 = {"B"};
    std::vector<std::string> exp2 = {"A"};
    std::vector<std::string> exp3 = {"B"};
    ASSERT_EQ(stateTab[key1], exp1);
    ASSERT_EQ(stateTab[key2], exp2);
    ASSERT_EQ(stateTab[key3], exp3);
}

TEST(StateTableTests, NoSuffixForLastPrefix) {
    std::vector<std::string> words = {"A", "B", "C", "D", "A", "B"};
    TextGeneratorClass generator("");
    auto stateTab = generator.buildStateTab(words);
    ASSERT_EQ(stateTab.size(), 4);
}

class SuffixSelectionTests : public ::testing::Test {
 protected:
  void SetUp() override {
    mockStateTab = {
        {{"X", "Y"}, {"Z"}},
        {{"A", "B"}, {"C", "D", "E"}},
        {{"M", "N"}, {}},
        {{"P", "Q"}, {"R", "R", "R"}}};
    generator.SetStateTab(mockStateTab);
  }
  TextGeneratorClass generator{""};
  std::map<prefix, std::vector<std::string>> mockStateTab;
  std::mt19937 gen{42};
};

TEST_F(SuffixSelectionTests, SingleSuffixSelection) {
    prefix key = {"X", "Y"};
    std::string result = generator.chooseNextWord(key, gen);
    ASSERT_EQ(result, "Z");
}

TEST_F(SuffixSelectionTests, MultipleSuffixesWithFixedSeed) {
    prefix key = {"A", "B"};
    std::string result = generator.chooseNextWord(key, gen);
    ASSERT_EQ(result, "C");
}

TEST_F(SuffixSelectionTests, EmptySuffixList) {
    prefix key = {"M", "N"};
    std::string result = generator.chooseNextWord(key, gen);
    ASSERT_TRUE(result.empty());
}

TEST_F(SuffixSelectionTests, RepeatedSuffixes) {
    prefix key = {"P", "Q"};
    std::string result = generator.chooseNextWord(key, gen);
    ASSERT_EQ(result, "R");
}

TEST(GenerationTests, MultiplePrefixesFlow) {
    std::map<prefix, std::vector<std::string>> table = {
        {{"A", "B"}, {"C"}},
        {{"B", "C"}, {"D"}}};
    TextGeneratorClass generator("");
    generator.SetStateTab(table);
    generator.SetStartPrefix({"A", "B"});
    std::string text = generator.generateText();
    ASSERT_EQ(text, "A B C D ");
}

TEST(GenerationTests, EmptyStateTable) {
    TextGeneratorClass generator("");
    std::string text = generator.generateText();
    ASSERT_TRUE(text.empty());
}

TEST(GenerationTests, MaxLengthGeneration) {
    std::map<prefix, std::vector<std::string>> cyclicTable = {
        {{"A", "B"}, {"C"}},
        {{"B", "C"}, {"A"}},
        {{"C", "A"}, {"B"}}};
    TextGeneratorClass generator("");
    generator.SetStateTab(cyclicTable);
    generator.SetStartPrefix({"A", "B"});
    std::string text = generator.generateText();
    int word_count = 0;
    for (int i = 0; i < text.length(); ++i) {
        if (text[i] == ' ')
            word_count++;
    }
    ASSERT_EQ(word_count, MAXGEN);
}
