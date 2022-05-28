// Copyright 2022 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"

TEST(task1, test1) {
    std::vector<std::string> words{"What", "a", "beautiful", "day!"};
    Markov Gen(words, 3, 100);
    std::string output = Gen.TextGen();
    if (output[0] = 'W')
        ASSERT_STREQ("What a beautiful day! ", output.c_str());
    else
        ASSERT_STREQ("a beautiful day! ", output.c_str());
}

TEST(task2, test1) {
    std::vector<std::string> words{"Hello", "World"};
    Markov Gen(words, 2, 100);
    ASSERT_STREQ("Hello World ", Gen.TextGen().c_str());
}

TEST(task3, test1) {
    std::map<std::deque<std::string>, std::vector<std::string>> dict;
    dict[{"Enjoy", "the"}].push_back("ride");
    dict[{"the", "ride"}].push_back("<Last_Prefix>");
    Markov Gen(dict, 100);
    std::string output = Gen.TextGen();
    if (output[0] == 'E')
        ASSERT_STREQ("Enjoy the ride ", output.c_str());
    else
        ASSERT_EQ('t', output[0]);
}

TEST(task4, test1) {
    std::map<std::deque<std::string>, std::vector<std::string>> dict;
    dict[{"Enjoy", "the"}].push_back("ride");
    dict[{"Enjoy", "the"}].push_back("moment");
    dict[{"the", "ride"}].push_back("<Last_Prefix>");
    dict[{"the", "moment"}].push_back("<Last_Prefix>");

    Markov Gen(dict, 100);
    std::string output = Gen.TextGen();
    if (output[0] == 't')
        ASSERT_EQ('t', output[0]);
    else if (output[output[output.length() - 2]] == 'e')
        ASSERT_STREQ("Enjoy the ride ", output.c_str());
    else
        ASSERT_STREQ("Enjoy the moment ", output.c_str());
}

