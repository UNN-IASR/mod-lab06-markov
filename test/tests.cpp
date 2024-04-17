// Copyright 2024 Danil Volkov

#include <gtest/gtest.h>
#include <string>
#include "../include/textgen.h"

class MarkovChainTest : public testing::Test {
 protected:
    MarkovChain markovChain;
};

TEST(MarkovChainTest, PrefixFormation) {
    MarkovChain markovChain;

    std::string text = "I love my baby";
    int prefixLength = 2;

    markovChain.train(text, prefixLength);

    Prefix prefix = { "I", "love" };

    EXPECT_NE(markovChain.stateTable.find(prefix),
              markovChain.stateTable.end());
}

TEST(MarkovChainTest, PrefixSuffix) {
    MarkovChain markovChain;

    std::string text = "I love my baby";
    int prefixLength = 2;

    markovChain.train(text, prefixLength);

    Prefix prefix = { "I", "love" };

    EXPECT_EQ(markovChain.stateTable[prefix][0], "my");
}

TEST(MarkovChainTest, OnlySuffix) {
    MarkovChain markovChain;

    std::string text = "I love my baby";
    int prefixLength = 2;
    int maxgen = 9;

    markovChain.train(text, prefixLength);
    std::string result = markovChain.generate(maxgen, 123);

    EXPECT_EQ(result, "I love my");
}

TEST(MarkovChainTest, ManySuffixes) {
    MarkovChain markovChain;

    std::string text = "I love my baby, I love my home, I love my eat";
    int prefixLength = 2;
    int maxgen = 14;

    markovChain.train(text, prefixLength);
    std::string result = markovChain.generate(maxgen, 302);

    EXPECT_EQ(result, "I love my eat");
}

TEST(MarkovChainTest, ManualTable) {
    MarkovChain markovChain;

    std::string text = "I love my baby, I love my home, I love my eat";
    int prefixLength = 2;
    int maxgen = 14;

    std::map<Prefix, std::vector<std::string>> stateTable = {
        {{"I", "love"}, {"my"}},
        {{"love", "my"}, {"baby", "eat"}},
        {{"my", "baby,"}, {"I"}},
        {{"baby,", "I"}, {"love"}}
    };


    markovChain.trainFromStateTable(stateTable);
    std::string result = markovChain.generate(maxgen, 302);


    EXPECT_EQ(result, "I love my eat");
}

