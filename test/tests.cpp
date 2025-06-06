// Copyright 2025 9hkge

#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "textgen.h"

std::map<prefix, std::vector<std::string>> get_test_map() {
  std::map<prefix, std::vector<std::string>> map;

  map[{"Жил", "старик"}] = {"со"};
  map[{"старик", "со"}] = {"своею"};
  map[{"со", "своею"}] = {"старухой"};

  return map;
}

// Создаёт и возвращает готовый генератор с заполненной таблицей
TextGenerator prepareGenerator() {
  TextGenerator gen(2, 42);  // prefix_size=2, seed=42
  gen.create_suffix_map(get_test_map());
  return gen;
}

TEST(TextGenTest, GenerateText_LengthIsCorrect) {
  TextGenerator gen(2, 42);  // префикс длины 2, сид 42
  std::istringstream input("the quick brown fox jumps over the lazy dog");
  gen.create_suffix_map(input);

  std::string result = gen.generate(5);

  std::istringstream stream(result);
  std::vector<std::string> words(std::istream_iterator<std::string>{stream},
                                  std::istream_iterator<std::string>());

  EXPECT_EQ(words.size(), 5);
}


TEST(TextGenTest, CorrectSuffixMapConstruction) {
  TextGenerator gen(2, 0);
  std::istringstream input("a b c d");
  gen.create_suffix_map(input);

  auto table = gen.get_suffix_map();

  prefix p1 = {"a", "b"};
  prefix p2 = {"b", "c"};

  ASSERT_EQ(table[p1].size(), 1);
  EXPECT_EQ(table[p1][0], "c");

  ASSERT_EQ(table[p2].size(), 1);
  EXPECT_EQ(table[p2][0], "d");
}



TEST(TextGenTest, EmptyInputReturnsEmptyString) {
  TextGenerator gen(2, 0);
  std::istringstream empty_input("");
  gen.create_suffix_map(empty_input);

  std::string result = gen.generate(10);

  EXPECT_TRUE(result.empty());
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

// 4. Выбор одного суффикса из нескольких (ПСЧ)
TEST(TextGenTest, RandomSuffixChoiceFromMultiple) {
  TextGenerator generator(1, 42);
  std::map<prefix, std::vector<std::string>> map = {
      {{"Жил"}, {"старик", "волк", "гном"}}
  };
  generator.create_suffix_map(map);

  std::string result = generator.generate(5);
  EXPECT_EQ(result.find("Жил"), 0);// начинается с "Жил"
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
  EXPECT_EQ(count, 3);
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
TEST(TextGenTest, OutputStartsWithKnownPrefix) {
  auto generator = prepareGenerator();
  generator.create_suffix_map(get_test_map());
  std::string result = generator.generate(4);

  // Получаем первый префикс из карты суффиксов
  auto suffix_map = generator.get_suffix_map();
  ASSERT_FALSE(suffix_map.empty());

  // Берём один из ключей (префиксов)
  prefix first_prefix = suffix_map.begin()->first;

  // Собираем строку из слов префикса для проверки начала
  std::string prefix_str = first_prefix[0];
  for (size_t i = 1; i < first_prefix.size(); ++i) {
    prefix_str += " " + first_prefix[i];
  }

  // Проверяем, что результат начинается с этого префикса
  EXPECT_EQ(result.compare(0, prefix_str.size(), prefix_str), 0);
}
