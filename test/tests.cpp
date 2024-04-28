// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"

TEST(Test1, SizeStatetab) {
    std::string text = "Hello world! How are you?";
    Markov mark = Markov();

    std::map<prefix, suffixes> map = mark.GenerateStatetab(2, text);

    EXPECT_EQ(8, map.size());
}

TEST(Test2, SizeSuffixes1) {
    std::string text = "Hello world! How are you?";
    Markov mark = Markov();

    std::map<prefix, suffixes> map = mark.GenerateStatetab(2, text);

    for (auto pair : map) {
        EXPECT_EQ(2, pair.first.size());
    }
}

TEST(Test3, SizeSuffixes2) {
    std::string text = "hello world how are you hello world \
        I'm here hello world are you fine";
    Markov mark = Markov();

    std::map<prefix, suffixes> map = mark.GenerateStatetab(2, text);

    prefix pref1;
    pref1.push_back("hello");
    pref1.push_back("world");

    prefix pref2;
    pref2.push_back("you");
    pref2.push_back("hello");

    EXPECT_EQ(map[pref1].size(), 3);
    EXPECT_EQ(map[pref2].size(), 1);
}

TEST(Test4, CurrentSuffixes) {
    std::string text = "hello world how are you hello world \
        I'm here hello world are you fine";
    Markov mark = Markov();

    std::map<prefix, suffixes> map = mark.GenerateStatetab(2, text);

    prefix pref1;
    pref1.push_back("are");
    pref1.push_back("you");

    EXPECT_EQ(map[pref1].at(0), "hello");
    EXPECT_EQ(map[pref1].at(1), "fine");
}

TEST(Test5, SizeResultText) {
    std::string text = "hello world how you fine thanks hello world";
    Markov mark = Markov();
    auto result = mark.GenerateText(text, 2, 7);

    EXPECT_EQ(mark.Split(result).size(), 7);
}
