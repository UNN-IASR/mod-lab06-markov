// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>

#include <sstream>

#include "textgen.h"

TEST(MarkovTest, Prefix2Validation) {
  MarkovChain gen(2);
  PrefixDeque pref = {"a", "b"};
  gen.addWordTransition(pref, "c");
  ASSERT_EQ("c", gen.getNextWord(pref));
}

TEST(MarkovTest, Prefix3Validation) {
  MarkovChain gen(3);
  PrefixDeque pref = {"a", "b", "c"};
  gen.addWordTransition(pref, "d");
  ASSERT_EQ(gen.getNextWord(pref).size(), 1);
}

TEST(MarkovTest, SingleTransition) {
  MarkovChain gen(1);
  gen.addWordTransition({"a"}, "b");
  EXPECT_EQ(gen.getNextWord({"a"}), "b");
}

TEST(MarkovTest, MultiTransition) {
  MarkovChain gen(1);
  gen.addWordTransition({"a"}, "b");
  gen.addWordTransition({"a"}, "c");
  std::string result = gen.getNextWord({"a"});
  EXPECT_TRUE(result == "b" || result == "c");
}

TEST(MarkovTest, OutputLengthCheck) {
  MarkovChain gen(2);
  gen.addWordTransition({"a", "b"}, "c");
  gen.addWordTransition({"b", "c"}, "d");
  std::string text = gen.generate(4);
  std::istringstream iss(text);
  int count = 0;
  std::string word;
  while (iss >> word) count++;
  EXPECT_EQ(count, 4);
}

TEST(MarkovTest, EmptyInputCase) {
  MarkovChain gen(2);
  EXPECT_EQ(gen.generate(5), "");
}

TEST(MarkovTest, SingleWordGeneration) {
  MarkovChain gen(1);
  gen.addWordTransition({"a"}, "a");
  std::string text = gen.generate(3);
  std::string filtered;
  for (char c : text) {
    if (c != '\n') filtered += c;
  }
  if (!filtered.empty() && filtered.back() == ' ') {
    filtered.pop_back();
  }
  EXPECT_EQ(filtered, "a a a");
}

TEST(MarkovTest, CyclicGeneration) {
  MarkovChain gen(1);
  gen.addWordTransition({"a"}, "b");
  gen.addWordTransition({"b"}, "a");
  std::string text = gen.generate(4);
  std::string filtered;
  for (char c : text) {
    if (c != '\n') filtered += c;
  }
  if (!filtered.empty() && filtered.back() == ' ') {
    filtered.pop_back();
  }
  EXPECT_TRUE(filtered == "a b a b" || filtered == "b a b a");
}

TEST(MarkovTest, PrefixStructure) {
  MarkovChain gen(2);
  PrefixDeque pref = {"a", "b"};
  PrefixDeque expectedLast = {"b", "c"};
  gen.addWordTransition(pref, "c");
  ASSERT_EQ(expectedLast, gen.getFinalPrefix());
}

TEST(MarkovTest, InitialStateCheck) {
  MarkovChain gen(3);
  PrefixDeque pref = {"a", "b", "c"};
  gen.addWordTransition(pref, "d");
  ASSERT_EQ(gen.getNextWord(pref), "d");
}
