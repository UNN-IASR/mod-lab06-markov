// Copyright 2025 9hkge

#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "textgen.h"



// Утилита для создания генератора с префиксом размера 2
TextGenerator prepareGenerator(int prefix_size = 2) {
  return TextGenerator(prefix_size, 42);
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



// 4. Выбор одного суффикса из нескольких (ПСЧ)
TEST(TextGenTest, RandomSuffixChoiceFromMultiple) {
  TextGenerator generator(1, 42);
  std::map<prefix, std::vector<std::string>> map = {
      {{"Жил"}, {"старик", "волк", "гном"}}
  };
  generator.create_suffix_map(map);

  std::string result = generator.generate(5);
  EXPECT_EQ(result.find("Жил"), 0u);
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
  std::istringstream iss(result);
  int count = std::distance(std::istream_iterator<std::string>(iss),
                            std::istream_iterator<std::string>());
  EXPECT_EQ(count, 2);
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

  std::string result = generator.generate(10);
  std::istringstream iss(result);
  int words = std::distance(std::istream_iterator<std::string>(iss),
                            std::istream_iterator<std::string>());
  EXPECT_LT(words, 10);
}

// 10. Проверка корректности начального префикса в выходной строке
TEST(TextGenTest, OutputStartsWithInitialPrefix) {
  auto generator = prepareGenerator();
  generator.create_suffix_map(get_test_map());
  std::string result = generator.generate(4);
  EXPECT_EQ(result.find("Жил старик"), 0u);
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
