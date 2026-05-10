// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"
#include <sstream>

class TextGenTest : public ::testing::Test {
protected:
    TextGen gen;
};

TEST_F(TextGenTest, PrefixLengthTest) {
    std::deque<std::string> pref = { "word1", "word2" };
    EXPECT_EQ(pref.size(), TextGen::NPREF);
}

TEST_F(TextGenTest, TablePopulationTest) {
    std::istringstream iss("one two three four");
    gen.readText(iss);
    EXPECT_EQ(gen.getTableSize(), 2);
}

TEST_F(TextGenTest, PrefixSuffixMappingTest) {
    std::istringstream iss("a b c");
    gen.readText(iss);
    std::deque<std::string> key = { "a", "b" };
    EXPECT_EQ(gen.statetab[key][0], "c");
}

TEST_F(TextGenTest, SingleSuffixTest) {
    std::istringstream iss("apple banana orange");
    gen.readText(iss);
    std::deque<std::string> key = { "apple", "banana" };
    
    EXPECT_EQ(gen.statetab[key].size(), 1);
    EXPECT_EQ(gen.statetab[key][0], "orange");
    
    std::string result = gen.generate(3);
    EXPECT_EQ(result, "apple banana orange");
}

TEST_F(TextGenTest, MultipleSuffixesTest) {
    std::istringstream 
    iss("I love Masha I love Kirill I love Garden");
    gen.readText(iss);
    std::deque<std::string> key = { "I", "love" };
    EXPECT_GE(gen.statetab[key].size(), 2);
}

TEST_F(TextGenTest, ExactLengthCharTest) {
    std::istringstream 
    iss("It's like a long text yeah, it's actually very long");
    gen.readText(iss);
    std::string result = gen.generate(50);
    EXPECT_GE(result.length(), 50);
}

TEST_F(TextGenTest, EmptyInputTest) {
    std::istringstream iss("");
    gen.readText(iss);
    EXPECT_EQ(gen.generate(100), "");
}

TEST_F(TextGenTest, ManualTableGeneration) {
    gen.statetab[{"start", "here"}] = { "end" };
    std::string result = gen.generate(10);
    EXPECT_NE(result.find("start here end"), std::string::npos);
}

TEST_F(TextGenTest, LoopDetectionTest) {
    std::istringstream iss("a b a b a b a b");
    gen.readText(iss);
    std::string result = gen.generate(20);
    EXPECT_FALSE(result.empty());
}

TEST_F(TextGenTest, ResetOnDeadEndTest) {
    std::istringstream iss("end of road");
    gen.readText(iss);
    std::string result = gen.generate(100);
    EXPECT_GE(result.length(), 100);
}
