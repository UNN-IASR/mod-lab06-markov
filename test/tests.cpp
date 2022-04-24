// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "textgen.h"

TEST(task1, test1) {
    TextGen tg = TextGen("Text2.txt", 2);
    std::string text = tg.CreateText(1000);
    TextGen::prefix temp = tg.GetPref(0);
    ASSERT_EQ(temp.size(), 2);
}

TEST(task2, test1) {
    TextGen tg = TextGen("Text3.txt", 2);
    std::string text = tg.CreateText(1000);
    TextGen::prefix temp = tg.GetPref(0);
    std::vector<std::string> temporarySuffix = tg.ChooseSuffix(temp);
    ASSERT_EQ(temporarySuffix[0], "family");
}

TEST(task3, test1) {
    TextGen tg = TextGen("Text3.txt", 2);
    std::string text = tg.CreateText(1000);
    TextGen::prefix temp = tg.GetPref(1);
    std::vector<std::string> temporarySuffix = tg.statetab.at(temp);
    ASSERT_EQ(temporarySuffix[0], "There");
}

TEST(task4, test1) {
    TextGen tg = TextGen("Text4.txt", 2);
    std::string text = tg.CreateText(1000);
    TextGen::prefix temp = tg.GetPref(1);
    std::string result = tg.ChooseAnySuffix(temp);
    EXPECT_TRUE(result == "red" || result == "and");
}

TEST(task5, test1) {
    TextGen tg = TextGen("Text5.txt", 2);
    std::string text = tg.CreateText(1000);
    TextGen::prefix temp = tg.GetPref(0);
    std::vector<std::string> temporarySuffix = tg.ChooseSuffix(temp);
    ASSERT_EQ(temporarySuffix[0], "brother");
}
