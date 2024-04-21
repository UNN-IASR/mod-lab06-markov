// Copyright 2024 Vyacheslav Bolshakov
#include <gtest/gtest.h>
#include "../include/textgen.h"

TEST(mgenerator, test1) {
    MGenerator mgen;
    mgen.read_text("I am Vyacheslav", 2);
    prefix pref = {"I", "am"};
    EXPECT_EQ(mgen.statetab.begin()->first, pref);
}

TEST(mgenerator, test2) {
    MGenerator mgen;
    mgen.read_text("I am Vyacheslav", 2);
    prefix pref = {"I", "am"};
    EXPECT_EQ(mgen.statetab[pref][0], "Vyacheslav");
}

TEST(mgenerator, test3) {
    MGenerator mgen;
    mgen.read_text("I have a cat", 1);
    std::string text = mgen.generate_text(3);
    bool check = (text == "I have a ") || (text == "have a cat ") ||
        (text == "a cat ") || (text == "cat ");
    ASSERT_TRUE(check);
}

TEST(mgenerator, test4) {
    MGenerator mgen;
    mgen.read_text("a cat a dog", 1);
    prefix pref = {"a"};
    std::vector<std::string> suf = {"cat", "dog"};
    EXPECT_EQ(mgen.statetab[pref], suf);
}

TEST(mgenerator, test5) {
    MGenerator mgen;
    mgen.statetab = {
        {{"i"}, {"have"}},
        {{"have"}, {"a"}},
        {{"a"}, {"cat", "dog"}}
    };
    mgen.prefixes = {{"i"}, {"have"}, {"a"}};
    std::string text = mgen.generate_text(2);
    bool check = (text == "i have ") || (text == "have a ") ||
        (text == "a cat ") || (text == "a dog ");
    ASSERT_TRUE(check);
}
