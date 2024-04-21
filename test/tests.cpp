// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"

TEST(test1, prefix) {
  TextGen textgen;
  std::string words = "I am student";
  prefix pref = {"I", "am"};
  textgen.makeTab(words, 2);
  EXPECT_EQ(textgen.statetab.find(pref),
  textgen.statetab.end());
}

TEST(test3, suffix) {
    std::string words = "I am student";
    TextGen textgen;
    textgen.makeTab(words, 1);
    EXPECT_EQ(textgen.generateText(5, 50), "I Iam");
}

TEST(test4, chooseSuffix) {
    std::string words = "I am person, I am student, I am not a programist";
    TextGen textgen;
    textgen.makeTab(words, 2);
    EXPECT_EQ(textgen.generateText(9, 100), "I Iam Iam");
}

TEST(test5, text) {
    typedef std::deque<std::string> prefix;
    std::map<prefix, std::vector<std::string> > state = {
        { { "a" }, { "A", "a" } },
        { { "b" }, { "B", "b" } },
        { {"c"}, {"C"} }
    };
    TextGen textgen;
    typedef std::deque<std::string> prefix;
    prefix pref{ "a" };
    textgen.statetab = state;
    textgen.first = pref;
    EXPECT_EQ(textgen.generateText(10, 10), "a A ");
}
