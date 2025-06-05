// Copyright 2025 9hkge
#include <gtest/gtest.h>
#include "textgen.h"
#include <sstream>

// Утилита для создания генератора с префиксом размера 2
TextGenerator prepareGenerator(int prefix_size = 2) {
    return TextGenerator(prefix_size, 42); // фиксированное зерно ПСЧ для предсказуемости
}

// Утилита: создаёт словарь вручную
std::map<prefix, std::vector<std::string>> get_test_map() {
    prefix p1 = {"Жил", "старик"};
    prefix p2 = {"старик", "со"};
    prefix p3 = {"со", "своею"};
    return {
        {p1, {"со"}},
        {p2, {"своею"}},
        {p3, {"старухой"}}
    };
}

// 1. Проверка формирования префикса
TEST(TextGenTest, FormPrefixFromWords) {
    std::istringstream input("Жил старик со своею старухой");
    TextGenerator generator = prepareGenerator();

    generator.create_suffix_map(input);
    auto map = generator.get_suffix_map();

    prefix expected = {"Жил", "старик"};
    ASSERT_TRUE(map.find(expected) != map.end());
    EXPECT_EQ(map[expected][0], "со");
}

// 2. Проверка записи "префикс-суффикс"
TEST(TextGenTest, PrefixSuffixEntryCorrectness) {
    auto generator = prepareGenerator();
    generator.create_suffix_map(get_test_map());

    auto map = generator.get_suffix_map();
    prefix test_prefix = {"со", "своею"};

    ASSERT_TRUE(map.find(test_prefix) != map.end());
    EXPECT_EQ(map[test_prefix][0], "старухой");
}

// 3. Выбор одного суффикса из одного варианта (детерминированность)
TEST(TextGenTest, SingleSuffixChoice) {
    auto generator = prepareGenerator();
    generator.create_suffix_map(get_test_map());

    std::string generated = generator.generate(3);
    EXPECT_NE(generated.find("Жил старик со"), std::string::npos);
}

// 4. Выбор одного суффикса из нескольких (ПСЧ)
TEST(TextGenTest, RandomSuffixChoiceFromMultiple) {
    TextGenerator generator(1, 42);
    std::map<prefix, std::vector<std::string>> map = {
        {{"Жил"}, {"старик", "волк", "гном"}}
    };
    generator.create_suffix_map(map);

    std::string result = generator.generate(5);
    EXPECT_TRUE(result.find("Жил") == 0); // начинается с "Жил"
}

// 5. Проверка генерации текста заданной длины
TEST(TextGenTest, GenerateFixedLengthText) {
    auto generator = prepareGenerator();
    generator.create_suffix_map(get_test_map());

    std::string result = generator.generate(6);
    int word_count = std::count(result.begin(), result.end(), ' ');
    EXPECT_EQ(word_count, 6);
}

// 6. Генерация при пустом словаре
TEST(TextGenTest, EmptySuffixMapGeneratesNothing) {
    auto generator = prepareGenerator();
    std::string result = generator.generate(10);
    EXPECT_EQ(result, "");
}

// 7. Отказ при нуле или отрицательной длине
TEST(TextGenTest, ZeroOrNegativeLengthReturnsEmpty) {
    auto generator = prepareGenerator();
    EXPECT_EQ(generator.generate(0), "");
    EXPECT_EQ(generator.generate(-5), "");
}

// 8. Проверка удаления использованных суффиксов
TEST(TextGenTest, UsedSuffixIsRemoved) {
    TextGenerator generator(1, 42);
    std::map<prefix, std::vector<std::string>> map = {
        {{"а"}, {"б", "в", "г"}}
    };
    generator.create_suffix_map(map);
    std::string result = generator.generate(4);
    int count = std::count(result.begin(), result.end(), ' ');
    EXPECT_EQ(count, 4); // должно быть 4 слова
}

// 9. Проверка генерации при достижении конца возможных переходов
TEST(TextGenTest, EndsEarlyIfNoSuffixesLeft) {
    TextGenerator generator(2, 42);
    std::map<prefix, std::vector<std::string>> map = {
        {{"а", "б"}, {"в"}},
        {{"б", "в"}, {"г"}},
        {{"в", "г"}, {}}
    };
    generator.create_suffix_map(map);

    std::string result = generator.generate(10); // должно закончиться раньше
    int words = std::count(result.begin(), result.end(), ' ');
    EXPECT_LT(words, 10);
}

// 10. Проверка корректности начального префикса в выходной строке
TEST(TextGenTest, OutputStartsWithInitialPrefix) {
    auto generator = prepareGenerator();
    generator.create_suffix_map(get_test_map());
    std::string result = generator.generate(4);
    EXPECT_TRUE(result.find("Жил старик") == 0);
}
