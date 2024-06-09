// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"

TEST(Test1, PrefixFormation) {
    std::string text = "shut up and take my money! Take my money now!";
    Markov mark = Markov(text, 2);

    std::map<prefix, suffixes> map = mark.GetStatetab();

    for (auto pair : map) {
        EXPECT_EQ(2, pair.first.size());
    }
}

TEST(Test2, RecordFormation) {
    std::string text = "shut up and take my money! take my money now!";
    Markov mark = Markov(text, 2);

    std::map<prefix, suffixes> map = mark.GetStatetab();

    prefix pref1;
    pref1.push_back("shut");
    pref1.push_back("up");

    prefix pref2;
    pref2.push_back("take");
    pref2.push_back("my");

    EXPECT_EQ(map[pref1].size(), 1);
    EXPECT_EQ(map[pref2].size(), 2);
}

TEST(Test3, ChoosingSingleSuffix) {
    std::string text = "shut up and take my money! take my money now!";
    Markov mark = Markov(text, 2);

    std::map<prefix, suffixes> map = mark.GetStatetab();

    prefix pref1;
    pref1.push_back("shut");
    pref1.push_back("up");

    EXPECT_EQ(map[pref1].at(0), "and");
}

TEST(Test4, Choosing_suffix) {
    std::string text = "shut up and take my money! take my money now!";
    Markov mark = Markov(text, 2);

    std::map<prefix, suffixes> map = mark.GetStatetab();

    prefix pref1;
    pref1.push_back("shut");
    pref1.push_back("up");

    EXPECT_EQ(map[pref1].at(0), "and");
}


TEST(Test5, TextFormation) {
    std::string text = "shut up and take my money! take my money now!";
    Markov mark = Markov(text, 2);

    std::map<prefix, suffixes> map = mark.GetStatetab();

    std::string result = mark.GenerateText(6);

    EXPECT_EQ(SplitText(result).size(), 5);
}
