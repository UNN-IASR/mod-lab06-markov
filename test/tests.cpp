// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>

#include "textgen.h"

#include <string>

TEST(TextGenTest, Prefix2Check)
{
    TextGenerator gen(2);
    prefix pref = { "a", "b" };
    gen.addTransition(pref, "c");
    ASSERT_EQ("c", gen.genSuffix(pref));
}

TEST(TextGenTest, Prefix3Check)
{
    TextGenerator gen(3);
    prefix pref = { "a", "b", "c" };
    gen.addTransition(pref, "d");
    ASSERT_EQ(gen.genSuffix(pref).size(), 1);
}

TEST(TextGenTest, SingleSuffix)
{
    TextGenerator gen(1);
    gen.addTransition({ "a" }, "b");

    EXPECT_EQ(gen.genSuffix({ "a" }), "b");
}

TEST(TextGenTest, MultipleSuffixes)
{
    TextGenerator gen(1);
    gen.addTransition({ "a" }, "b");
    gen.addTransition({ "a" }, "c");

    std::string result = gen.genSuffix({ "a" });
    EXPECT_TRUE(result == "b" || result == "c");
}

TEST(TextGenTest, TextLength)
{
    TextGenerator gen(2);
    gen.addTransition({ "a", "b" }, "c");
    gen.addTransition({ "b", "c" }, "d");

    std::string text = gen.genText(4);
    std::istringstream iss(text);
    int wordCount = 0;
    std::string word;

    while (iss >> word) wordCount++;
    EXPECT_EQ(wordCount, 4);
}

TEST(TextGenTest, EmptyInput)
{
    TextGenerator gen(2);
    EXPECT_EQ(gen.genText(5), "");
}

TEST(TextGenTest, SingleWord)
{
    TextGenerator gen(1);
    gen.addTransition({ "a" }, "a");

    std::string text = gen.genText(3);
    std::string result = "";
    for (int i = 0; i < text.size(); i++) {
        if (text[i] != '\n') result += text[i];
    }
    if (result[result.size() - 1] == ' ') result.erase(result.size() - 1, 1);
    EXPECT_EQ(result, "a a a");
}

TEST(TextGenTest, CyclicDependencies)
{
    TextGenerator gen(1);
    gen.addTransition({ "a" }, "b");
    gen.addTransition({ "b" }, "a");

    std::string text = gen.genText(4);
    std::string result = "";
    for (int i = 0; i < text.size(); i++) {
        if (text[i] != '\n') result += text[i];
    }
    if (result[result.size() - 1] == ' ') result.erase(result.size() - 1, 1);
    EXPECT_TRUE(result == "a b a b" || result == "b a b a");
}

TEST(TextGenTest, PrefixForming)
{
    TextGenerator gen(2);
    prefix pref = { "a", "b" };
    prefix end_pref = { "b", "c" };
    gen.addTransition(pref, "c");
    ASSERT_EQ(end_pref, gen.getEnd());
}

TEST(TextGenTest, InitialPrefix)
{
    TextGenerator gen(3);
    prefix pref = { "a", "b", "c" };
    gen.addTransition(pref, "d");
    ASSERT_EQ(gen.genSuffix(pref), "d");
}
