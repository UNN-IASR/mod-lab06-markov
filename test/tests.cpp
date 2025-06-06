// Copyright 2025 9hkge

#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "textgen.h"

TEST(TextGenTest, FormsCorrectPrefixSize) {
  TextGenerator gen(2, 42);
  istringstream input("one two three four");
  gen.create_suffix_map(input);

  for (const auto& entry : gen.get_suffix_map()) {
      EXPECT_EQ(entry.first.size(), 2);
  }
}


TEST(TextGenTest, CreatesSinglePrefixSuffixPair) {
  TextGenerator gen(1, 42);
  istringstream input("hello world");
  gen.create_suffix_map(input);

  auto map = gen.get_suffix_map();
  deque<string> expected_prefix = {"hello"};

  ASSERT_EQ(map.size(), 1);
  EXPECT_EQ(map[expected_prefix][0], "world");
}


TEST(TextGenTest, CreatesMultiplePrefixSuffixPairs) {
  TextGenerator gen(1, 42);
  istringstream input("a b c");
  gen.create_suffix_map(input);

  auto map = gen.get_suffix_map();

  EXPECT_EQ(map[{"a"}][0], "b");
  EXPECT_EQ(map[{"b"}][0], "c");
}

TEST(TextGenTest, SelectsSingleSuffix) {
  TextGenerator gen(1, 42);
  map<deque<string>, vector<string>> m = {
      {{"a"}, {"b"}}
  };
  gen.create_suffix_map(m);

  string result = gen.generate(2);
  EXPECT_TRUE(result.find("a b") != string::npos);
}

TEST(TextGenTest, RandomlySelectsFromMultipleSuffixes) {
  TextGenerator gen(1, 42);
  map<deque<string>, vector<string>> m = {
      {{"a"}, {"b", "c", "d"}}
  };
  gen.create_suffix_map(m);

  string result = gen.generate(3);
  EXPECT_TRUE(result.find("a ") != string::npos);
}

TEST(TextGenTest, GeneratesEmptyTextIfLengthZero) {
  TextGenerator gen(2, 42);
  map<deque<string>, vector<string>> m = {
      {{"a", "b"}, {"c"}}
  };
  gen.create_suffix_map(m);

  string result = gen.generate(0);
  EXPECT_EQ(result, "");
}

TEST(TextGenTest, GeneratesTextOfExactLength) {
  TextGenerator gen(1, 42);
  map<deque<string>, vector<string>> m = {
      {{"a"}, {"b"}},
      {{"b"}, {"c"}},
      {{"c"}, {"d"}}
  };
  gen.create_suffix_map(m);

  string result = gen.generate(4);
  int word_count = count(result.begin(), result.end(), ' ');
  EXPECT_EQ(word_count, 4);
}

TEST(TextGenTest, StopsIfNoSuffixes) {
  TextGenerator gen(1, 42);
  map<deque<string>, vector<string>> m = {
      {{"a"}, {}}
  };
  gen.create_suffix_map(m);

  string result = gen.generate(5);
  int word_count = count(result.begin(), result.end(), ' ');
  EXPECT_EQ(word_count, 1);
}

TEST(TextGenTest, HandlesEmptyMap) {
  TextGenerator gen(1, 42);
  map<deque<string>, vector<string>> m = {};
  gen.create_suffix_map(m);

  string result = gen.generate(5);
  EXPECT_EQ(result, "");
}


TEST(TextGenTest, GeneratesSameOutputWithSameSeed) {
  map<deque<string>, vector<string>> m = {
      {{"a"}, {"b", "c", "d"}},
      {{"b"}, {"e"}},
      {{"c"}, {"f"}},
      {{"d"}, {"g"}}
  };

  TextGenerator gen1(1, 123);
  gen1.create_suffix_map(m);
  auto res1 = gen1.generate(5);

  TextGenerator gen2(1, 123);
  gen2.create_suffix_map(m);
  auto res2 = gen2.generate(5);

  EXPECT_EQ(res1, res2);
}

