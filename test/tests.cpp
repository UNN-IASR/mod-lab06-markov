// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "textgen.h"

TEST(task1, test1) {
    std::string text = "test1.txt";
    TextGenerator gentext = TextGenerator(text, 2, 1000);
    gentext.generate();
    int result = gentext.words.size();
    EXPECT_EQ(6, result);
}
