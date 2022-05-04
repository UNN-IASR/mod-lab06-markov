// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"
TEST(task1, test1) {
  Gen gn = Gen("123 234 567 1234", 3, 1000);
  string result = gn.getText();
  char* ch=new char[result.size()+1];
  strcpy(ch,result.c_str());
  ASSERT_STREQ("123 234 567 1234 ", ch);
}
TEST(task1, test2) {
  Gen gn = Gen("123 234", 1, 1000);
  string result = gn.getText();
  char* ch=new char[result.size()+1];
  strcpy(ch,result.c_str());
  ASSERT_STREQ("123 234 ", ch);
}
TEST(task1, test3) {
  map<deque<string>, vector<string> > str;
  str[{"123", "567"}].push_back("234");
  Gen gn = Gen(str, { "123","567","234" }, 2, 1000);
  string result = gn.getText();
  char* ch=new char[result.size()+1];
  strcpy(ch,result.c_str());
  ASSERT_STREQ("123 567 234 ", ch);
}
TEST(task1, test4) {
  map<deque<string>, vector<string> > str;
  str[{"123", "567"}].push_back("234");
  str[{"123", "567"}].push_back("000");
  str[{"123", "567"}].push_back("888");
  Gen gn = Gen(str, { "123","567","234", "000", "888" }, 2, 1000);
  string result = gn.getText();
  char* ch=new char[result.size()+1];
  strcpy(ch,result.c_str());
  ASSERT_STREQ("123 567 234 ", ch);
}
TEST(task1, test5) {
  Gen gn = Gen("aa bb cc dd aa bb", 2, 20);
  string result = gn.getText();
  char* ch=new char[result.size()+1];
  strcpy(ch,result.c_str());
  ASSERT_STREQ("aa bb cc dd aa bb cc ", ch);
}
