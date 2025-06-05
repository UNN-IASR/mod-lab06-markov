// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>

#include "textgen.h"

TEST(TextGenTest, PrefixHandling) {
  TextGenerator gen(2);
  prefix pref = {"word1", "word2"};
  gen.addTransition(pref, "word3");
  ASSERT_EQ("word3", gen.genSuffix(pref));
}

TEST(TextGenTest, MultipleTransitions) {
  TextGenerator gen(1);
  gen.addTransition({"choice"}, "option1");
  gen.addTransition({"choice"}, "option2");

  std::string result = gen.genSuffix({"choice"});
  EXPECT_TRUE(result == "option1" || result == "option2");
}

TEST(TextGenTest, WordCountControl) {
  TextGenerator gen(2);
  gen.addTransition({"a", "b"}, "c");
  gen.addTransition({"b", "c"}, "d");

  std::string text = gen.genText(5, 5);
  int spaces = std::count(text.begin(), text.end(), ' ');
  EXPECT_EQ(spaces + 1, 5);
}

TEST(TextGenTest, EmptyGenerator) {
  TextGenerator gen(2);
  EXPECT_TRUE(gen.genText(100, 150).empty());
}

TEST(TextGenTest, CyclicGeneration) {
  TextGenerator gen(1);
  gen.addTransition({"a"}, "b");
  gen.addTransition({"b"}, "a");

  std::string text = gen.genText(4, 4);
  text.erase(std::remove(text.begin(), text.end(), '\n'), text.end());
  if (!text.empty() && text.back() == ' ') text.pop_back();
  EXPECT_TRUE(text == "a b a b" || text == "b a b a");
}

TEST(TextGenTest, PrefixConsistency) {
  TextGenerator gen(2);
  prefix pref = {"first", "second"};
  gen.addTransition(pref, "third");
  EXPECT_EQ(gen.getEnd(), (prefix{"second", "third"}));
}

TEST(TextGenTest, InvalidRange) {
  TextGenerator gen(1);
  gen.addTransition({"test"}, "value");
  EXPECT_THROW(gen.genText(1500, 1000), std::invalid_argument);
}

TEST(TextGenTest, SingleWordOutput) {
  TextGenerator gen(3);
  gen.addTransition({"x", "y", "z"}, "w");
  EXPECT_EQ(gen.genText(1, 1), "x y z w");
}

TEST(TextGenTest, MinWords) {
  TextGenerator gen(2);
  gen.addTransition({"start", "text"}, "generation");
  gen.addTransition({"text", "generation"}, "test");

  std::string text = gen.genText(1000, 1500);
  int words = std::count(text.begin(), text.end(), ' ') + 1;
  EXPECT_GE(words, 1000);
}

TEST(TextGenTest, TransitionAddition) {
  TextGenerator gen(1);
  gen.addTransition({"a"}, "b");
  EXPECT_EQ(gen.genSuffix({"a"}), "b");
}
