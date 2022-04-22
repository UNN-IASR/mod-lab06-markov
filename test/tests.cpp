// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"
#define rand_r rand

TEST(task1, test1) {
  std::string text = "t1.txt";
  genText gn = genText(text, 2, 1000);
  int result = gn.words.size();
  EXPECT_EQ(9, result);
}

TEST(task2, test2) {
  std::string text = "t1.txt";
  genText gn = genText(text, 2, 1000);
  typedef std::deque<std::string> prefix;
  prefix pre;
  pre.push_back("love");
  pre.push_back("you,");
  std::string result = gn.statetab[pre][0];
  EXPECT_EQ("baby", result);
}

TEST(task3, test3) {
  srand(4561);
  std::string text = "t1.txt";
  genText gn = genText(text, 2, 1000);
  typedef std::deque<std::string> prefix;  // prefix
  prefix pre;
  pre.push_back("love");
  pre.push_back("you,");
  int s = gn.statetab[pre].size();
  int veroyatnost = rand_r() % gn.statetab[pre].size();
  std::string suf = gn.statetab[pre][veroyatnost];
  int result = 0;
  if (s == 1 && suf == "baby")
    result = 1;
  EXPECT_EQ(1, result);
}

TEST(task4, test4) {
  srand(4561);
  std::string text = "t2.txt";
  genText gn = genText(text, 2, 1000);
  typedef std::deque<std::string> prefix;
  prefix pre;
  pre.push_back("you,");
  pre.push_back("baby");
  int veroyatnost = rand_r() % gn.statetab[pre].size();
  std::string slovo = gn.statetab[pre][veroyatnost];
  int s = gn.statetab[pre].size();
  int result = 0;
  if (s == 3 && (slovo == "To" || slovo == "And" || slovo == "Trust"))
    result = 1;
  EXPECT_EQ(1, result);
}

TEST(task5, test5) {
  std::string text = "text3.txt";
  genText gn = genText(text, 2, 204);
  std::string answer = gn.getText();
  int s = answer.size();
  int result = 0;
  if (s >= 204)
    result = 1;
  EXPECT_EQ(1, result);
}
