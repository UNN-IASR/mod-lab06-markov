// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>

#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>

#include "textgen.h"

using std::deque;
using std::map;
using std::mt19937;
using std::random_device;
using std::string;
using std::unordered_set;
using std::vector;

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