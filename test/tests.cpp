// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "textgen.h"

TEST(task1, test1) {
    TextGen tg = TextGen("Text.txt", 2);
    std::string text = tg.CreateText(1000);
    TextGen::prefix temp = tg.GetPref(0);
    ASSERT_EQ(temp.size(), 2);
}
