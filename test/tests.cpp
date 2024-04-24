// Copyright 2024 Yuriy Nazarov
#include <gtest/gtest.h>
#include "textgen.h"

class TextGenTest : public testing::Test {
 protected:
    TextGen textgGen;
};

TEST(TextGenTest, PrefixFormation) {
    TextGen textGen;
    std::string text = "I like to move it, move it";
    int prefixLength = 2;
    textGen.TextProcessing(text, prefixLength);
    Prefix prefix = { "I", "like" };
    EXPECT_NE(textGen.statetab.find(prefix), textGen.statetab.end());
}

TEST(TextGenTest, PrefixSuffix) {
    TextGen textGen;
    std::string text = "I like to move it, move it";
    int prefixLength = 2;
    textGen.TextProcessing(text, prefixLength);
    Prefix prefix = { "I", "like" };
    EXPECT_EQ(textGen.statetab[prefix][0], "to");
}

TEST(TextGenTest, OnlySuffix) {
    TextGen textGen;
    std::string text = "I like to move it, move it";
    int prefixLength = 2;
    int maxgen = 9;
    textGen.TextProcessing(text, prefixLength);
    std::string result = textGen.GenerateText(maxgen);
    EXPECT_EQ(result, "I like to ");
}

TEST(TextGenTest, ManySuffixes) {
    TextGen textGen;
    std::string text = "I love my baby, I love my home, I love my eat";
    int prefixLength = 2;
    int maxgen = 14;
    textGen.TextProcessing(text, prefixLength);
    std::string result = textGen.GenerateText(maxgen);
    bool enabled = ((result.find("eat") != std::string::npos) ||
    (result.find("home") != std::string::npos) ||
    (result.find("baby") != std::string::npos));
    EXPECT_TRUE(enabled);
}

TEST(TextGenTest, ManualTable) {
    TextGen textGen;
    std::string text = "I love my baby, I love my home, I love my eat";
    int prefixLength = 2;
    int maxgen = 19;
    textGen.TextProcessing(text, prefixLength);
    std::string result = textGen.GenerateText(maxgen);
    bool enabled  = ((result.find("eat") != std::string::npos) ||
    (result.find("I love") != result.rfind("I love")));
    EXPECT_TRUE(enabled);
}
