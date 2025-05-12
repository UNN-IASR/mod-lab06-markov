// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <string>
#include "textgen.h"

// Тесты для формирования префикса из заданного числа слов
TEST(PrefixTest, TwoWordPrefix) {
    TextGenerator generator;
    generator.build_state_table(INPUT_FILE_PATH, 2);
    ASSERT_EQ(generator.get_init_pref().size(), 2);
}

TEST(PrefixTest, ThreeWordPrefix) {
    TextGenerator generator;
    generator.build_state_table(INPUT_FILE_PATH, 3);
    ASSERT_EQ(generator.get_init_pref().size(), 3);
}

TEST(PrefixTest, PrefixContent) {
    TextGenerator generator;
    generator.add_pref({"word1", "word2"}, "word3");
    prefix expected = {"word1", "word2"};
    ASSERT_EQ(generator.get_init_pref(), expected);
}

TEST(PrefixTest, EmptyPrefix) {
    TextGenerator generator;
    EXPECT_THROW(generator.build_state_table("nonexistent.txt", 2),
    std::runtime_error);
}

TEST(PrefixTest, PrefixShorterThanText) {
    TextGenerator generator;
    generator.build_state_table(INPUT_FILE_PATH, 1);
    ASSERT_EQ(generator.get_init_pref().size(), 1);
}


// Тесты для формирования записи "префикс-суффикс"
TEST(PrefixSuffixTest, SingleSuffixAddition) {
    TextGenerator generator;
    prefix pref = {"test", "prefix"};
    generator.add_pref(pref, "suffix");
    ASSERT_EQ(generator.get_table()[pref].size(), 1);
}

TEST(PrefixSuffixTest, MultipleSuffixesForPrefix) {
    TextGenerator generator;
    prefix pref = {"a", "b"};
    generator.add_pref(pref, "c");
    generator.add_pref(pref, "d");
    ASSERT_EQ(generator.get_table()[pref].size(), 2);
}

TEST(PrefixSuffixTest, SuffixContentVerification) {
    TextGenerator generator;
    prefix pref = {"hello", "world"};
    generator.add_pref(pref, "!");
    ASSERT_EQ(generator.get_table()[pref][0], "!");
}

TEST(PrefixSuffixTest, EmptySuffix) {
    TextGenerator generator;
    prefix pref = {"empty", "suffix"};
    generator.add_pref(pref, "");
    ASSERT_TRUE(generator.get_table()[pref][0].empty());
}

TEST(PrefixSuffixTest, MultiplePrefixes) {
    TextGenerator generator;
    generator.add_pref({"a", "b"}, "c");
    generator.add_pref({"d", "e"}, "f");
    ASSERT_EQ(generator.get_table().size(), 2);
}

// Тесты для выбора суффикса (с использованием ПСЧ)
TEST(SuffixSelectionTest, SingleSuffixSelection) {
    TextGenerator generator;
    prefix pref = {"only", "one"};
    generator.add_pref(pref, "choice");
    ASSERT_EQ(generator.random_suff(pref), "choice");
}

TEST(SuffixSelectionTest, MultipleSuffixSelection) {
    TextGenerator generator;
    prefix pref = {"multiple", "choices"};
    generator.add_pref(pref, "a");
    generator.add_pref(pref, "b");
    generator.add_pref(pref, "c");

    std::string result = generator.random_suff(pref);
    EXPECT_TRUE(result == "a" || result == "b" || result == "c");
}

TEST(SuffixSelectionTest, SuffixDistribution) {
    TextGenerator generator;
    prefix pref = {"test", "distribution"};
    generator.add_pref(pref, "a");
    generator.add_pref(pref, "b");

    // Проверяем, что оба варианта могут быть выбраны
    bool hasA = false, hasB = false;
    for (int i = 0; i < 100; ++i) {
        std::string result = generator.random_suff(pref);
        if (result == "a") hasA = true;
        if (result == "b") hasB = true;
    }
    EXPECT_TRUE(hasA && hasB);
}

TEST(SuffixSelectionTest, EmptySuffixSelection) {
    TextGenerator generator;
    prefix pref = {"empty", "vector"};
    EXPECT_THROW(generator.random_suff(pref), std::runtime_error);
}

TEST(SuffixSelectionTest, SingleCharSuffix) {
    TextGenerator generator;
    prefix pref = {"single", "char"};
    generator.add_pref(pref, "x");
    ASSERT_EQ(generator.random_suff(pref).size(), 1);
}

// Тесты для формирования текста заданной длины
TEST(TextGenerationTest, ExactLengthGeneration) {
    TextGenerator generator;
    generator.add_pref({"start", "text"}, "middle");
    generator.add_pref({"text", "middle"}, "end");
    generator.generate_text(OUTPUT_FILE_PATH, 4);

    std::ifstream file(OUTPUT_FILE_PATH);
    int wordCount = 0;
    std::string word;
    while (file >> word) wordCount++;

    ASSERT_EQ(wordCount, 4);
}

TEST(TextGenerationTest, EmptyStateTable) {
    TextGenerator generator;
    EXPECT_THROW(generator.generate_text(OUTPUT_FILE_PATH, 10),
    std::runtime_error);
}

TEST(TextGenerationTest, EndPrefixReached) {
    TextGenerator generator;
    generator.add_pref({"a", "b"}, "c");
    generator.add_pref({"b", "c"}, "d");
    generator.add_end_pref({"c", "d"});
    generator.generate_text(OUTPUT_FILE_PATH, 100);

    std::ifstream file(OUTPUT_FILE_PATH);
    int wordCount = 0;
    std::string word;
    while (file >> word) wordCount++;

    EXPECT_LT(wordCount, 100);
}

TEST(TextGenerationTest, LineBreaksInOutput) {
    TextGenerator generator;
    generator.add_pref({"line", "break"}, "test");
    generator.generate_text(OUTPUT_FILE_PATH, 20);

    std::ifstream file(OUTPUT_FILE_PATH);
    std::string line;
    bool hasLineBreak = false;
    while (std::getline(file, line)) {
        if (line.find("test") != std::string::npos && !line.empty()) {
            hasLineBreak = true;
        }
    }
    EXPECT_TRUE(hasLineBreak);
}

TEST(TextGenerationTest, WordCleaningVerification) {
    TextGenerator generator;
    generator.add_pref({"clean", "word"}, "test!");
    generator.generate_text("output.txt", 3);

    std::ifstream file(OUTPUT_FILE_PATH);
    std::string content;
    std::getline(file, content);

    EXPECT_EQ(content.find("test!"), std::string::npos);
    EXPECT_NE(content.find("test"), std::string::npos);
}

TEST(TextGenerationTest, GeneralTest) {
    TextGenerator generator_markova;
    generator_markova.build_state_table(INPUT_FILE_PATH,
        generator_markova.NPREF);
    generator_markova.generate_text(OUTPUT_FILE_PATH,
        generator_markova.MAXGEN);

    std::ifstream file(OUTPUT_FILE_PATH);
    int wordCount = 0;
    std::string word;
    while (file >> word) wordCount++;

    ASSERT_GT(wordCount, 1000);
}

