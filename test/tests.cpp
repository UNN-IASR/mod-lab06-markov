// Copyright 2022 UNN-IASR
#include <gtest/gtest.h>
#include "textgen.h"

TEST(task1, test1) {
    std::string text = "test1.txt";
    TextGenerator gentext = TextGenerator(text, 2, 1000);
    typedef std::deque<std::string> prefix;
    prefix pre;
    pre.push_back("test");
    pre.push_back("will");
    std::string result = gentext.stateTab[pre][0];
    EXPECT_EQ("be", result);
}
