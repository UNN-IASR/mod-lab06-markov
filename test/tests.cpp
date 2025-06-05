// Copyright 2021 GHA Test Team

#include "textgen.h"

#include <algorithm>
#include <deque>
#include <sstream>
#include <stdexcept>
#include <string>

#include <gtest/gtest.h>

using std::deque;
using std::istringstream;
using std::string;
using std::stringstream;

TEST(TextGenTest, PrefixHandling) {
  TextGenerator gen(2);
  deque<string> pref = {"word1", "word2"};
  gen.addTransition(pref, "word3");

  ASSERT_EQ("word3", gen.genSuffix(pref));
}

TEST(TextGenTest, MultipleTransitions) {
  TextGenerator gen(1);
  gen.addTransition({"choice"}, "option1");
  gen.addTransition({"choice"}, "option2");

  string result = gen.genSuffix({"choice"});
  EXPECT_TRUE(result == "option1" || result == "option2");
}

TEST(TextGenTest, WordCountControl) {
  TextGenerator gen(2);
  gen.addTransition({"a", "b"}, "c");
  gen.addTransition({"b", "c"}, "d");
  gen.addTransition({"c", "d"}, "e");

  string output = gen.genText(5, 5);
  std::istringstream iss(output);
  int wordCount = 0;
  string word;

  while (iss >> word) wordCount++;
  EXPECT_EQ(wordCount, 5);
}

TEST(TextGenTest, EmptyGenerator) {
  TextGenerator gen(2);
  EXPECT_TRUE(gen.genText(100, 150).empty());
}

TEST(TextGenTest, CyclicGeneration) {
  TextGenerator gen(1);
  gen.addTransition({"a"}, "b");
  gen.addTransition({"b"}, "a");

  string output = gen.genText(4, 4);
  output.erase(remove(output.begin(), output.end(), '\n'), output.end());
  if (!output.empty() && output.back() == ' ') output.pop_back();

  EXPECT_TRUE(output == "a b a b" || output == "b a b a");
}

TEST(TextGenTest, FileLoading) {
  TextGenerator gen("test_input.txt", 2);
  string output = gen.genText(10, 10);
  EXPECT_FALSE(output.empty());
}

TEST(TextGenTest, MinMaxWords) {
  TextGenerator gen(2);
  gen.addTransition({"start", "text"}, "generation");
  gen.addTransition({"text", "generation"}, "test");

  string output = gen.genText(1000, 1500);
  int wordCount = count(output.begin(), output.end(), ' ') + 1;
  EXPECT_GE(wordCount, 1000);
  EXPECT_LE(wordCount, 1500);
}

TEST(TextGenTest, PrefixConsistency) {
  TextGenerator gen(2);
  deque<string> pref = {"first", "second"};
  gen.addTransition(pref, "third");

  EXPECT_EQ(gen.getEnd(), (deque<string>{"second", "third"}));
}

TEST(TextGenTest, InvalidRange) {
  TextGenerator gen(1);
  gen.addTransition({"test"}, "value");

  EXPECT_THROW(gen.genText(1500, 1000), std::invalid_argument);
}

TEST(TextGenTest, EdgeCases) {
  TextGenerator gen(3);
  gen.addTransition({"x", "y", "z"}, "w");

  string output = gen.genText(1, 1);
  EXPECT_EQ(output, "x y z w");
}
