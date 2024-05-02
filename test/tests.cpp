// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <string>
#include "textgen.h"

class GenerateTest : public testing::Test {};

TEST(GenerateTest, TestPrefix) {
    std::string text = "Once there lived an old man and old woman";
    const int NREF = 2;

    textgen gen(text, NREF);

    textgen::Prefix prefix = { "Once", "there" };

    EXPECT_NE(gen.stateTable.find(prefix), gen.stateTable.end());
}

TEST(GenerateTest, TestPrefixSuffix) {
    std::string text = "Once there lived an old man and old woman";
    const int NREF = 2;

    textgen gen(text, NREF);

    textgen::Prefix prefix = { "Once", "there" };

    EXPECT_EQ(gen.stateTable[prefix][0], "lived");
}

TEST(GenerateTest, TestOnceSuffix) {
    std::string text = "Once there lived an old man and old woman";
    const int NREF = 2;

    textgen gen(text, NREF);

    const int MAXGEN = 1;
    std::string result = gen.generate(MAXGEN);

    EXPECT_EQ(result, "Once there lived ");
}

TEST(GenerateTest, TestVectorSuffix) {
    std::string text = "aa bb cc x aa bb cc y aa bb cc z";
    const int NREF = 2;

    textgen gen(text, NREF);

    const int MAXGEN = 1;
    std::string result = gen.generate(MAXGEN);

    EXPECT_EQ(result, "aa bb cc ");
}

TEST(GenerateTest, TestTable) {
    std::map<textgen::Prefix, std::vector<std::string>> stateTable = {
        {{"aa", "bb"}, {"cc"}},
        {{"bb", "cc"}, {"x", "y"}},
        {{"cc", "x"}, {"aa"}},
        {{"x", "aa"}, {"bb"}}
    };

    textgen gen(stateTable);

    const int MAXGEN = 1;
    std::string result = gen.generate(MAXGEN);

    EXPECT_EQ(result, "aa bb cc ");
}
