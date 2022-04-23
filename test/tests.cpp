// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "textgen.h"

TEST(test1, constrPref) {
  textgen t = textgen("test1.txt", 2);
  std::string text = t.CreateText(1000);
  textgen::prefix temp = t.GetPref(0);
  ASSERT_EQ(temp.size(), 2);
}

TEST(test2, suffixMatch) {
  textgen t = textgen("test1.txt", 2);
  std::string text = t.CreateText(1000);
  textgen::prefix temp = t.GetPref(0);
  std::vector<std::string> tempSuff = t.GetSuff(temp);
  ASSERT_EQ(tempSuff[0], "three");
}

TEST(test3, pickOnlySuff) {
  textgen t = textgen("test1.txt", 2);
  std::string text = t.CreateText(1000);
  textgen::prefix temp = t.GetPref(1);
  std::vector<std::string> tempSuff = t.statetab.at(temp);
  ASSERT_EQ(tempSuff[0], "four");
}

TEST(test4, pickSuffixFromOptions) {
  textgen t = textgen("test2.txt", 2);
  std::string text = t.CreateText(1000);
  textgen::prefix temp = t.GetPref(1);
  std::string result = t.GetCertainSuffix(temp);
  EXPECT_TRUE(result == "four" || result == "seven");
}

TEST(test5, createTest) {
  textgen t = textgen("forTesting.txt", 2);
  std::string text = t.CreateText(1000);
  int count = 0;
  for (int i = 0; i < text.size(); i++) {
    if (text[i] == ' ')
      count++;
    }
  std::cout << text;
  ASSERT_EQ(count, 83);
}
