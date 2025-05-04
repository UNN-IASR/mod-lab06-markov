// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"
#include <sstream>
#include <fstream>
#include <iterator>
#include <cstdlib>

TEST(TextGeneratorTest, PrefixFormation) {
    TextGenerator generator;
    std::istringstream input("one two three four");
    generator.build(input);

    ASSERT_EQ(generator.initialPrefix.size(), TextGenerator::NPREF);
}

TEST(TextGeneratorTest, PrefixSuffixEntrySingle) {
    TextGenerator generator;
    std::istringstream input("one two three");
    generator.build(input);

    TextGenerator::prefix p = { "one", "two" };
    ASSERT_EQ(generator.statetab[p].size(), 1);
    ASSERT_EQ(generator.statetab[p][0], "three");
}

TEST(TextGeneratorTest, PrefixSuffixEntryMultiple) {
    TextGenerator generator;
    std::istringstream input("one two three one two four one two five");
    generator.build(input);

    TextGenerator::prefix p = { "one", "two" };
    ASSERT_EQ(generator.statetab[p].size(), 3);
}

TEST(TextGeneratorTest, SingleSuffixSelection) {
    TextGenerator generator;
    std::istringstream input("one two three");
    generator.build(input);

    TextGenerator::prefix p = { "one", "two" };
    std::string next = generator.statetab[p][0];
    ASSERT_EQ(next, "three");
}

TEST(TextGeneratorTest, MultipleSuffixSelection) {
    TextGenerator generator;
    std::istringstream input("one two three one two four one two five");
    generator.build(input);

    srand(0);
    TextGenerator::prefix p = { "one", "two" };
    size_t index = rand() % generator.statetab[p].size();
    ASSERT_TRUE(index >= 0 && index < generator.statetab[p].size());
}

TEST(TextGeneratorTest, TextGenerationLength) {
    TextGenerator generator;
    std::istringstream input("one two three four five six seven eight nine ten");
    generator.build(input);

    const std::string testFile = "test_output.txt";
    generator.generate(5, testFile);

    std::ifstream in(testFile);
    std::string generatedText;
    std::getline(in, generatedText);

    std::istringstream iss(generatedText);
    int wordCount = std::distance(std::istream_iterator<std::string>(iss),
        std::istream_iterator<std::string>());

    ASSERT_EQ(wordCount, 5 + TextGenerator::NPREF);
    std::remove(testFile.c_str());
}

TEST(TextGeneratorTest, EmptyInputFile) {
    TextGenerator generator;
    std::istringstream input("");

    EXPECT_THROW(generator.build(input), std::runtime_error);
}

TEST(TextGeneratorTest, PunctuationHandling) {
    TextGenerator generator;
    std::istringstream input("Hello, world! How are you?");
    generator.build(input);

    TextGenerator::prefix p = { "Hello,", "world!" };
    ASSERT_EQ(generator.statetab[p][0], "How");
}

TEST(TextGeneratorTest, RepeatedSequences) {
    TextGenerator generator;
    std::istringstream input("a b c a b d a b e");
    generator.build(input);

    TextGenerator::prefix p = { "a", "b" };
    ASSERT_EQ(generator.statetab[p].size(), 3);
}

TEST(TextGeneratorTest, InsufficientDataGeneration) {
    TextGenerator generator;
    std::istringstream input("only two words");
    generator.build(input);

    testing::internal::CaptureStderr();
    generator.generate(100);
    std::string output = testing::internal::GetCapturedStderr();

    ASSERT_TRUE(output.find("no data available") != std::string::npos);
}

TEST(TextGeneratorTest, FileOutputTest) {
    TextGenerator generator;
    std::istringstream input("this is a test for file output");
    generator.build(input);

    const std::string testFile = "test_output.txt";
    generator.generate(5, testFile);

    std::ifstream in(testFile);
    ASSERT_TRUE(in.good());

    std::string content;
    std::getline(in, content);
    ASSERT_FALSE(content.empty());

    std::remove(testFile.c_str());
}

TEST(TextGeneratorTest, LongWordHandling) {
    TextGenerator generator;
    std::istringstream input("ThisIsAVeryLongWordWithNoSpaces AnotherLongWord");
    generator.build(input);

    TextGenerator::prefix p = { "ThisIsAVeryLongWordWithNoSpaces", "AnotherLongWord" };
    ASSERT_TRUE(generator.statetab.find(p) != generator.statetab.end());
}