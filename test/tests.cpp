// Copyright 2025 Sergho

#include <gtest/gtest.h>

#include <deque>
#include <fstream>
#include <string>
#include <vector>

#include "textgen.h"

TEST(suffix_tests, single_variant) {
  map<deque<string>, vector<string>> table = {
      {{"a", "b"}, {"c"}}, {{"b", "c"}, {"d"}}, {{"c", "d"}, {"e"}}};

  TextGenerator generator(table);
  deque<string> prefix = {"b", "c"};
  string word = generator.nextWord(prefix);
  EXPECT_EQ("d", word);
}

TEST(suffix_tests, several_variants) {
  map<deque<string>, vector<string>> table = {{{"a", "b"}, {"c"}},
                                              {{"a", "b"}, {"d"}}};

  TextGenerator generator(table);
  deque<string> prefix = {"a", "b"};
  string word = generator.nextWord(prefix);
  EXPECT_TRUE(word == "c" || word == "d");
}

TEST(suffix_tests, no_variants) {
  map<deque<string>, vector<string>> table = {{{"a", "b"}, {"c"}},
                                              {{"a", "b"}, {"d"}}};

  TextGenerator generator(table);
  deque<string> prefix = {"a", "c"};
  string word = generator.nextWord(prefix);
  EXPECT_TRUE(word == "a" || word == "b");
}

TEST(get_table_tests, single_variant) {
  map<deque<string>, vector<string>> table = {{{"a", "b"}, {"c"}},
                                              {{"c", "d"}, {"e"}}};

  TextGenerator generator(table);
  EXPECT_EQ("a b: c\nc d: e\n", generator.getTable());
}

TEST(get_table_tests, several_variants) {
  map<deque<string>, vector<string>> table = {{{"a", "b"}, {"c", "d"}},
                                              {{"c", "d"}, {"e"}}};

  TextGenerator generator(table);
  EXPECT_EQ("a b: c\na b: d\nc d: e\n", generator.getTable());
}

TEST(pseudo_random_tests, single_variant) {
  map<deque<string>, vector<string>> table = {{{"a", "b"}, {"c"}},
                                              {{"c", "d"}, {"e"}}};

  TextGenerator generator(table);
  generator.fixRandomDevice(42);
  deque<string> prefix = {"a", "b"};
  EXPECT_EQ("c", generator.nextWord(prefix));
}

TEST(pseudo_random_tests, several_variants) {
  map<deque<string>, vector<string>> table = {{{"a", "b"}, {"c", "d", "e"}},
                                              {{"c", "d"}, {"e"}}};

  TextGenerator generator(table);
  generator.fixRandomDevice(42);
  deque<string> prefix = {"a", "b"};
  EXPECT_EQ("d", generator.nextWord(prefix));
}

TEST(text_tests, simple_table) {
  map<deque<string>, vector<string>> table = {{{"a", "b"}, {"c", "d", "e"}},
                                              {{"c", "d"}, {"e", "f"}}};

  TextGenerator generator(table);
  generator.fixRandomDevice(42);
  string text = generator.generateText(10);
  EXPECT_EQ("a b e c a c c c c a ", text);
}

TEST(text_tests, loop_table) {
  map<deque<string>, vector<string>> table = {{{"a", "b"}, {"c", "d"}},
                                              {{"b", "c"}, {"d", "e"}},
                                              {{"c", "d"}, {"e", "f"}},
                                              {{"d", "e"}, {"f", "a"}},
                                              {{"e", "f"}, {"a", "b"}}};

  TextGenerator generator(table);
  generator.fixRandomDevice(42);
  string text = generator.generateText(10);
  EXPECT_EQ("b c e e b e e d d b ", text);
}

TEST(file_tests, input_file_exists) {
  std::ofstream file("./test_input.txt");
  file << "жил старик со своею старухой у самого синего моря";
  file.close();
  TextGenerator generator("./test_input.txt");
  generator.fixRandomDevice(42);
  string text = generator.generateText(10);
  EXPECT_EQ("своею старухой у самого синего моря старухой со со моря ", text);
}

TEST(file_tests, input_file_not_found) {
  EXPECT_THROW(
      { TextGenerator generator("./not_exists.txt"); }, std::invalid_argument);
}

TEST(file_tests, output_file) {
  std::ofstream file("./test_input.txt");
  file << "жил старик со своею старухой у самого синего моря";
  file.close();
  TextGenerator generator("./test_input.txt");
  generator.fixRandomDevice(42);
  string text = generator.generateText("./test_output.txt", 10);
  std::ifstream outFile("./test_output.txt");
  EXPECT_EQ(true, outFile.good());
  outFile.close();
}
