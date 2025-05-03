// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <deque>
#include <map>
#include <sstream>

#include "textgen.h"

int countWords(const std::string& str) {
    std::stringstream stream(str);
    std::string word;
    int count = 0;
    while (stream >> word) {
        count++;
    }
    return count;
}

TEST(MarkovGeneratorTest, CanCreateObject) {
    MarkovTextGenerator generator;
    ASSERT_TRUE(true);
}

const std::vector<std::string> testWords = {"один",
 "два", "три", "один", "два", "четыре"};

TEST(MarkovGeneratorTest, CorrectStartPrefixIsStored) {
    MarkovTextGenerator generator;
    generator.createTable(testWords);
    const prefix& start_prefix = generator.getStartPrefix();
    prefix expectStart = {"один", "два"};
    ASSERT_EQ(start_prefix, expectStart);
}

TEST(MarkovGeneratorTest, CorrectTableSize) {
    MarkovTextGenerator generator;
    generator.createTable(testWords);
    const statetab& table = generator.getTable();
    ASSERT_EQ(table.size(), 3);
}

TEST(MarkovGeneratorTest, PrefixSuffixPairCorrect_1) {
    MarkovTextGenerator generator;
    generator.createTable(testWords);
    const statetab& table = generator.getTable();
    prefix key = {"два", "три"};
    auto it = table.find(key);
    ASSERT_NE(it, table.end());
    std::vector<std::string> expectSuffixes = {"один"};
    ASSERT_EQ(it->second, expectSuffixes);
}

TEST(MarkovGeneratorTest, PrefixSuffixPairCorrect_2) {
    MarkovTextGenerator generator;
    generator.createTable(testWords);
    const statetab& table = generator.getTable();
    prefix key = {"три", "один"};
    auto it = table.find(key);
    ASSERT_NE(it, table.end());
    std::vector<std::string> expectSuffixes = {"два"};
    ASSERT_EQ(it->second, expectSuffixes);
}

TEST(MarkovGeneratorTest, PrefixWithMultipleSuffixesCorrect) {
    MarkovTextGenerator generator;
    generator.createTable(testWords);
    const statetab& table = generator.getTable();
    prefix key = {"один", "два"};
    auto it = table.find(key);
    ASSERT_NE(it, table.end());
    std::vector<std::string> expectSuffixes = {"три", "четыре"};
    ASSERT_EQ(it->second, expectSuffixes);
}

TEST(MarkovGeneratorTest, HandleEmptyInput) {
    MarkovTextGenerator generator;
    std::vector<std::string> emptyWords;
    ASSERT_NO_THROW(generator.createTable(emptyWords));
    ASSERT_TRUE(generator.getTable().empty());
    ASSERT_TRUE(generator.getStartPrefix().empty());
}

TEST(MarkovGeneratorTest, HandleShortInput) {
    MarkovTextGenerator generator;
    std::vector<std::string> short_words = {"слово1", "слово2"};
    ASSERT_NO_THROW(generator.createTable(short_words));
    ASSERT_TRUE(generator.getTable().empty());
    ASSERT_TRUE(generator.getStartPrefix().empty());
}

TEST(MarkovGeneratorTest, SingleSuffixChoiceLeadsToCorrectWord) {
    MarkovTextGenerator generator;
    std::vector<std::string> words = {"a", "b", "c", "d", "e"};
    generator.createTable(words);
    std::string text = generator.generateText();
    ASSERT_NE(text.find("a b c "), std::string::npos);
}

// Test from velichaishiy neironka
TEST(MarkovGeneratorTest, MultipleSuffixChoiceSelectsValidWord) {
    MarkovTextGenerator generator;
    // После "x y" идет либо "z1", либо "z2"
    std::vector<std::string> words = {"x",
     "y", "z1", "stop1", "x", "y", "z2", "stop2"};
    generator.createTable(words);

    std::string text = generator.generateText();

    // Ищем первое вхождение "x y "
    size_t pos = text.find("x y ");
    ASSERT_NE(pos, std::string::npos); // Убедимся, что нашли

    // Находим начало следующего слова
    size_t next_word_start = pos + std::string("x y ").length();
    // Находим конец следующего слова (до пробела)
    size_t next_word_end = text.find(" ", next_word_start);
    if (next_word_end == std::string::npos) {
        next_word_end = text.length();
    }

    // Выделяем следующее слово
    std::string next_word = text.substr(next_word_start,
     next_word_end - next_word_start);

    bool is_valid_suffix = (next_word == "z1" || next_word == "z2");
    ASSERT_TRUE(is_valid_suffix);
}

TEST(MarkovGeneratorTest, GeneratedTextStartsWithCorrectPrefix) {
    MarkovTextGenerator generator;
    std::vector<std::string> words = {"старт1",
     "старт2", "дальше", "слова"};
    generator.createTable(words);
    std::string text = generator.generateText();
    std::string expectStart = "старт1 старт2 ";
    ASSERT_EQ(text.substr(0, expectStart.length()), expectStart);
}

TEST(MarkovGeneratorTest, GeneratedTextLengthIsLimited) {
    MarkovTextGenerator generator;
    std::vector<std::string> words = {"a", 
    "b", "c", "a", "b", "d", "c", "a", "b"};
    generator.createTable(words);
    std::string text = generator.generateText();
    int wordCnt = countWords(text);
    ASSERT_LE(wordCnt, MAXGEN);
}
