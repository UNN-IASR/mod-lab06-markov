// Copyright 2024 alenkaLo
#include <gtest/gtest.h>
#include "../include/textgen.h"
//#include "../src/textgen.cpp"


TEST(TestCaseName, TestName1) {
    std::string path = "test/test.txt";
    std::map<prefix, std::vector<std::string>> statetab;
    statetab = ReadFile(2, path);
    prefix start = { "I", "can" };
    std::vector <std::string> exp = { "swim," , "run,"};
    EXPECT_EQ(statetab[start], exp);
}

TEST(TestCaseName, TestName2) {
    std::string path = "test/test.txt";
    std::map<prefix, std::vector<std::string>> statetab;
    statetab =  ReadFile(2, path);
    prefix pref;
    pref = statetab.begin()->first;
    size_t result = pref.size();
    EXPECT_EQ(result, 2);
}

TEST(TestCaseName, TestName3) {
    std::string path = "test/test.txt";
    //I can swim, I can run, I am strong and beautiful.
    std::map<prefix, std::vector<std::string>> statetab;
    statetab = ReadFile(2, path);
    std::map<prefix, std::vector<std::string>> exp = {
        {{"I", "can"}, {"swim,", "run,"}},
        {{"can", "run,"}, {"I"}},
        {{"swim,", "I"}, {"can"}},
        {{"can", "swim,"}, {"I"}},
        {{"run,", "I"}, {"am"}},
        {{"I", "am"}, {"strong"}},
        {{"am", "strong"}, {"and"}},
         {{"strong", "and"}, {"beautiful."}}
    };
    EXPECT_EQ(statetab, exp);
}

TEST(TestCaseName, TestName4) {
    std::map<prefix, std::vector<std::string>> statetab = {
        {{"I", "can"}, {"swim,", "run,"}},
        {{"can", "run,"}, {"I"}},
        {{"swim,", "I"}, {"can"}},
        {{"can", "swim,"}, {"I"}},
        {{"run,", "I"}, {"am"}},
        {{"I", "am"}, {"strong"}},
        {{"am", "strong"}, {"and"}},
         {{"strong", "and"}, {"beautiful."}}
    };
    std::string text = "";
    prefix start = { "can", "run," };
    std::string chooseSuffix = genWord(&start, statetab, &text);
    EXPECT_EQ(chooseSuffix, "I");
}

TEST(TestCaseName, TestName5) {
    std::map<prefix, std::vector<std::string>> statetab = {
        {{"I", "can"}, {"swim,", "run,"}},
        {{"can", "run,"}, {"I"}},
        {{"swim,", "I"}, {"can"}},
        {{"can", "swim,"}, {"I"}},
        {{"run,", "I"}, {"am"}},
        {{"I", "am"}, {"strong"}},
        {{"am", "strong"}, {"and"}},
         {{"strong", "and"}, {"beautiful."}}
    };
    std::string text = "";
    prefix start = { "I", "can" };
    std::string chooseSuffix = genWord(&start, statetab, &text);
    EXPECT_TRUE(chooseSuffix == "swim," || chooseSuffix == "run,");
}

TEST(TestCaseName, TestName6) {
    std::map<prefix, std::vector<std::string>> statetab = {
        {{"I", "can"}, {"swim,", "run,"}},
        {{"can", "run,"}, {"I"}},
        {{"swim,", "I"}, {"can"}},
        {{"can", "swim,"}, {"I"}},
        {{"run,", "I"}, {"am"}},
        {{"I", "am"}, {"strong"}},
        {{"am", "strong"}, {"and"}},
         {{"strong", "and"}, {"beautiful."}}
    };
    std::string text = "I am strong and beautiful. ";
    prefix start = { "can", "run," };
    EXPECT_EQ(generateText(2, 5, start, statetab), text);
}

