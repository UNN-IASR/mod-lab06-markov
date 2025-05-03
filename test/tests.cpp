// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <string>
#include <map>
#include <vector>
#include <set>
#include "textgen.h"

class MarkovChainTest : public testing::Test {
 protected:
    MarkovChain mc;
};

TEST(TextGenTest, FormsCorrectPrefixLength) {
    MarkovChain mc;
    std::string text = "one two three four five";
    mc.train(text, 2);

    for (const auto& entry : mc.stateTable) {
        EXPECT_EQ(entry.first.size(), 2);
    }
}

TEST(TextGenTest, HandlesSingleWordPrefix) {
    MarkovChain mc;
    std::string text = "single prefix test";
    mc.train(text, 1);

    for (const auto& entry : mc.stateTable) {
        EXPECT_EQ(entry.first.size(), 1);
    }
}

TEST(TextGenTest, CreatesCorrectPrefixSuffixMapping) {
    MarkovChain mc;
    std::string text = "a b c a b d";
    mc.train(text, 2);

    Prefix prefix;
    prefix.push_back("a");
    prefix.push_back("b");

    ASSERT_EQ(mc.stateTable[prefix].size(), 2);
    EXPECT_EQ(mc.stateTable[prefix][0], "c");
    EXPECT_EQ(mc.stateTable[prefix][1], "d");
}

TEST(TextGenTest, HandlesEmptyInput) {
    MarkovChain mc;
    std::string text = "";
    mc.train(text, 2);
    EXPECT_TRUE(mc.stateTable.empty());
}

TEST(TextGenTest, SelectsSingleSuffixDeterministically) {
    MarkovChain mc;
    std::map<Prefix, std::vector<std::string>> stateTable;
    Prefix prefix;
    prefix.push_back("the");
    prefix.push_back("cat");
    stateTable[prefix] = { "sat" };

    mc.trainFromStateTable(stateTable);
    std::string result = mc.generate(11, 42);

    EXPECT_EQ(result, "the cat sat");
}

TEST(TextGenTest, GeneratesTextFromManualStateTable) {
    MarkovChain mc;
    std::map<Prefix, std::vector<std::string>> stateTable;

    Prefix prefix1;
    prefix1.push_back("I");
    prefix1.push_back("am");
    stateTable[prefix1] = { "happy", "sad" };

    Prefix prefix2;
    prefix2.push_back("am");
    prefix2.push_back("happy");
    stateTable[prefix2] = { "today" };

    mc.trainFromStateTable(stateTable);
    std::string result = mc.generate(20, 42);

    EXPECT_TRUE(result.find("I am") != std::string::npos);
}

TEST(TextGenTest, GeneratesTextOfExactLength) {
    MarkovChain mc;
    std::string text = "this is a test for exact length generation";
    mc.train(text, 2);

    std::string result = mc.generate(10);
    EXPECT_EQ(result.size(), 9);
}

TEST(TextGenTest, HandlesUnknownPrefixesDuringGeneration) {
    MarkovChain mc;
    std::map<Prefix, std::vector<std::string>> stateTable;
    Prefix prefix;
    prefix.push_back("known");
    prefix.push_back("prefix");
    stateTable[prefix] = { "end" };

    mc.trainFromStateTable(stateTable);

    Prefix unknownPrefix;
    unknownPrefix.push_back("unknown");
    unknownPrefix.push_back("prefix");
    mc.startWord = unknownPrefix;

    std::string result = mc.generate(20);
    EXPECT_TRUE(result.empty());
}

TEST(TextGenTest, SplitsTextCorrectly) {
    MarkovChain mc;
    std::string text = "word1 word2 word3";
    auto words = mc.splitText(text);

    ASSERT_EQ(words.size(), 3);
    EXPECT_EQ(words[0], "word1");
    EXPECT_EQ(words[1], "word2");
    EXPECT_EQ(words[2], "word3");
}

TEST(TextGenTest, PrefixLengthAffectsOutput) {
    MarkovChain mc;
    std::string text = "A B C D A B E D A F C D A B C D A G H I J K L M N O P";

    std::set<std::string> results1;
    std::set<std::string> results2;

    for (int i = 0; i < 20; ++i) {
        mc.train(text, 1);
        results1.insert(mc.generate(20, i));

        mc.train(text, 2);
        results2.insert(mc.generate(20, i));
    }

    bool has_difference = false;
    for (const auto& res : results1) {
        if (results2.count(res) == 0) {
            has_difference = true;
            break;
        }
    }

    EXPECT_TRUE(has_difference);

    EXPECT_GT(results1.size(), 5);
    EXPECT_GT(results2.size(), 5);
}

TEST(TextGenTest, HandlesPunctuationInText) {
    MarkovChain mc;
    std::string text = "Hello, world! How are you?";
    mc.train(text, 2);

    std::string result = mc.generate(20, 123);
    EXPECT_FALSE(result.empty());
}

TEST(TextGenTest, HandlesEmptySuffixVector) {
    MarkovChain mc;
    std::map<Prefix, std::vector<std::string>> stateTable;
    Prefix prefix;
    prefix.push_back("empty");
    prefix.push_back("suffix");
    stateTable[prefix] = {};

    mc.trainFromStateTable(stateTable);
    mc.startWord = prefix;

    std::string result = mc.generate(20);
    EXPECT_EQ(result, "empty suffix");
}
