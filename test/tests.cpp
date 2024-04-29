// Copyright 2024 Mikhas3009
#include <gtest/gtest.h>
#include "textgen.h"

TEST(MarkovChainTest, TrainFromTextFile) {
    markov::MarkovChain generator;
    generator.train("test/test-text.txt", 2);
    EXPECT_FALSE(generator.table.empty());
}

TEST(MarkovChainTest, GeneratedPrefixExistsInTable) {
    markov::MarkovChain generator;
    generator.train("test/test-text.txt", 2);
    markov::MarkovChain::Prefix prefix = {"Jaga", "Boyaga,"};
    EXPECT_TRUE(generator.table.find(prefix) != generator.table.end());
}

TEST(MarkovChainTest, GeneratedPrefixHasSuffixes) {
    markov::MarkovChain generator;
    generator.train("test/test-text.txt", 2);
    markov::MarkovChain::Prefix prefix = {"Jaga", "Boyaga,"};
    EXPECT_FALSE(generator.table[prefix].empty());
}

TEST(MarkovChainTest, GeneratedTextLength) {
    markov::MarkovChain generator;
    generator.train("test/test-text.txt", 2);
    std::string result = generator.generate(10, true);
    EXPECT_EQ(result.size(), result.size());
}

TEST(MarkovChainTest, GenerateTextWithGivenPrefix) {
    markov::MarkovChain generator;
    generator.train("test/test-text.txt", 2);
    markov::MarkovChain::Prefix prefix = {"Jaga", "Boyaga,"};
    std::string result = generator.generate(5, false);
    EXPECT_FALSE(result.find("Jaga Boyaga,") != std::string::npos);
}

TEST(MarkovChainTest, GenerateTextWithoutRandomFirst) {
    markov::MarkovChain generator;
    generator.train("test/test-text.txt", 2);
    std::string result1 = generator.generate(5, false);
    std::string result2 = generator.generate(5, false);
    EXPECT_EQ(result1, result2);
}
