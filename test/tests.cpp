#include <gtest/gtest.h>
#include "../include/textgen.h"

TEST(MarkovChainTest, EmptyTextTraining) {
    TextGenerator gen;
    std::vector<std::string> text = {};
    gen.train(text);
    EXPECT_TRUE(gen.getStatetab().empty());
}

TEST(MarkovChainTest, ShortTextTraining) {
    TextGenerator gen;
    std::vector<std::string> text = { "одно", "слово" }; // –азмер <= NPREF
    gen.train(text);
    EXPECT_TRUE(gen.getStatetab().empty());
}

TEST(MarkovChainTest, PrefixFormation) {
    TextGenerator gen;
    std::vector<std::string> text = { "раз", "два", "три" };
    gen.train(text);
    prefix expected_prefix = { "раз", "два" };
    EXPECT_EQ(gen.getStartingPrefix(), expected_prefix);
}

TEST(MarkovChainTest, StateTablePopulation) {
    TextGenerator gen;
    std::vector<std::string> text = { "раз", "два", "три", "четыре" };
    gen.train(text);

    auto table = gen.getStatetab();
    prefix pref1 = { "раз", "два" };
    EXPECT_EQ(table[pref1].size(), 1);
    EXPECT_EQ(table[pref1][0], "три");
}

TEST(MarkovChainTest, MultipleSuffixesForPrefix) {
    TextGenerator gen;
    // ѕрефикс "раз два" встречаетс€ дважды
    std::vector<std::string> text = { "раз", "два", "три", "раз", "два", "четыре" };
    gen.train(text);

    auto table = gen.getStatetab();
    prefix pref = { "раз", "два" };
    EXPECT_EQ(table[pref].size(), 2);
    EXPECT_EQ(table[pref][0], "три");
    EXPECT_EQ(table[pref][1], "четыре");
}

TEST(MarkovChainTest, GenerateSingleSuffixLogic) {
    TextGenerator gen;
    std::vector<std::string> text = { "мама", "мыла", "раму" };
    gen.train(text);
    // ƒолжно вернуть ровно "мама мыла раму", так как вариантов больше нет
    EXPECT_EQ(gen.generate(10), "мама мыла раму");
}

TEST(MarkovChainTest, RandomSuffixSelection) {
    TextGenerator gen;
    std::vector<std::string> text = { "€", "люблю", "€блоки", "€", "люблю", "груши" };
    gen.train(text);

    std::string result = gen.generate(3);
    // –езультат должен быть либо "€ люблю €блоки", либо "€ люблю груши"
    bool is_valid = (result == "€ люблю €блоки" || result == "€ люблю груши");
    EXPECT_TRUE(is_valid);
}

TEST(MarkovChainTest, StopWhenNoSuffix) {
    TextGenerator gen;
    std::vector<std::string> text = { "один", "два", "три" };
    gen.train(text);
    // ѕросим 10 слов, но алгоритм должен остановитьс€ на 3, так как дальше цепь рветс€
    std::string result = gen.generate(10);
    EXPECT_EQ(result, "один два три");
}

TEST(MarkovChainTest, MaxLengthRestriction) {
    TextGenerator gen;
    // «ацикленный текст: "a b a b a b..."
    std::vector<std::string> text = { "a", "b", "a", "b", "a" };
    gen.train(text);

    std::string result = gen.generate(4);
    // ѕровер€ем, что алгоритм не выдал больше 4 слов
    int spaces = 0;
    for (char c : result) {
        if (c == ' ') spaces++;
    }
    EXPECT_EQ(spaces, 3); // 4 слова = 3 пробела
}

TEST(MarkovChainTest, CustomTableGeneration) {
    TextGenerator gen;
    std::vector<std::string> text = { "шел", "дождь", "и", "было", "холодно" };
    gen.train(text);

    std::string result = gen.generate(5);
    EXPECT_EQ(result, "шел дождь и было холодно");
}