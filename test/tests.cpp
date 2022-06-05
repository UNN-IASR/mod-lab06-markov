// Copyright 2022 UNN-IASR
#include <gtest/gtest.h>
#include "textgen.h"

TEST(task1, test1) {
    std::string text = "test1.txt";
    TextGenerator gentext = TextGenerator(text, 2, 1000);
    std::cout << gentext.generate();
    prefix pref;
    pref.push_back("test");
    pref.push_back("will");
    std::string result = gentext.stateTab[pref][0];
    EXPECT_EQ("be", result);
}
