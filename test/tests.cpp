//Copyright 2024 <levkovich-polina>
#include <gtest/gtest.h>
#include "textgen.h"

TEST(TestCaseName1, Test1) {
  std::string filename = "test1.txt";

  int prefixLength = 2;

  std::map<std::string, std::vector<std::string>> markovChain;

  text text;
  markovChain = text.read(filename, markovChain, prefixLength);
  bool flag = true;
  if (text.prefix.size() != 2) flag = false;

  EXPECT_TRUE(flag);
}
TEST(TestCaseName2, Test2) {
  std::string filename = "test1.txt";

  int prefixLength = 2;

  std::map<std::string, std::vector<std::string>> markovChain;

  text text;
  markovChain = text.read(filename, markovChain, prefixLength);
  std::string s = markovChain["My name"][0];
  EXPECT_EQ(s, "is");
}
TEST(TestCaseName3, Test3) {
  std::string filename = "test1.txt";

  int prefixLength = 1;

  std::map<std::string, std::vector<std::string>> markovChain;

  text text;
  markovChain = text.read(filename, markovChain, prefixLength);
  std::string s = markovChain["My"][0];
  EXPECT_EQ(s, "name");
}
TEST(TestCaseName4, Test4) {
  std::string filename = "test1.txt";

  int prefixLength = 2;

  std::map<std::string, std::vector<std::string>> markovChain;

  text text;
  markovChain = text.read(filename, markovChain, prefixLength);
  std::string s1 = markovChain["My name"][0];
  std::string s2 = markovChain["name is"][0];
  EXPECT_EQ(s1, "is");
  EXPECT_EQ(s2, "Polina");
}
TEST(TestCaseName5, Test5) {
  std::string filename = "test1.txt";
  bool flag = false;

  int prefixLength = 2;

  std::map<std::string, std::vector<std::string>> markovChain;

  int textLength = 3;

  text text;
  markovChain = text.read(filename, markovChain, prefixLength);
  text.generate(markovChain, prefixLength, textLength);
  std::string s1 = "My name is";
  std::string s2 = "name is ";
  if (text.generateText == s1 || text.generateText == s2) flag = true;
  //EXPECT_EQ(text.generateText, "name is ");
  EXPECT_TRUE(flag);
}
