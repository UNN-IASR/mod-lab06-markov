// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"

TEST(test1, prefixNumber) {
  MarkovTextGenerator g = MarkovTextGenerator(2, 1000);
  g.readFromFile("input.txt");
  int count = g.start.size();

  EXPECT_EQ(2, count);
}

TEST(test2, prefixSuffix) {
  MarkovTextGenerator g = MarkovTextGenerator(2, 1000);
  g.readFromFile("input.txt");
  std::map<std::deque<std::string>, std::vector<std::string> >::iterator it;
  it = g.statetab.find(g.start);
  std::string suff = it->second[0];

  EXPECT_EQ("the", suff);
}

TEST(test3, oneSuffix) {
  MarkovTextGenerator g = MarkovTextGenerator(2, 1000);
  g.readFromFile("test3_4.txt");

  std::map<std::deque<std::string>, std::vector<std::string> >::iterator it;
  it = g.statetab.find(g.start);
  std::string suff = it->second[rand() % (it->second).size()];

  EXPECT_EQ("my", suff);
}

TEST(test4, chooseSuffix) {
  MarkovTextGenerator g = MarkovTextGenerator(1, 1000);
  g.readFromFile("test3_4.txt");
  std::map<std::deque<std::string>, std::vector<std::string> >::iterator it;
  it = g.statetab.find(g.start);
  std::string suff = it->second[rand() % (it->second).size()];

  EXPECT_TRUE(suff == "ball" || suff == "cat" || suff == "car");
}

TEST(test5, lengthText) {
  MarkovTextGenerator g = MarkovTextGenerator(2, 33);

  std::string str;

  g.next.push_back("I");
  g.next.push_back("love");

  g.start = g.next;
  g.statetab[g.next].push_back("flowers");
  g.next.pop_front();
  g.next.push_back("flowers");

  g.statetab[g.next].push_back("I");
  g.next.pop_front();
  g.next.push_back("I");

  g.statetab[g.next].push_back("love");
  g.next.pop_front();
  g.next.push_back("love");

  g.statetab[g.next].push_back("books");
  g.next.pop_front();
  g.next.push_back("books");

  g.statetab[g.next].push_back("I");
  g.next.pop_front();
  g.next.push_back("I");

  g.statetab[g.next].push_back("love");
  g.next.pop_front();
  g.next.push_back("love");

  g.statetab[g.next].push_back("cats");
  g.next.pop_front();
  g.next.push_back("cats");

  g.statetab[g.next].push_back("I");
  g.next.pop_front();
  g.next.push_back("I");

  g.statetab[g.next].push_back("love");
  g.next.pop_front();
  g.next.push_back("love");

  g.generateNewText();

  int count = g.countWords;

  EXPECT_EQ(33, count);
}
