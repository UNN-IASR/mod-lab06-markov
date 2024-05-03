// Copyright 2024 katione
#include <gtest/gtest.h>
#include <string>
#include "../include/textgen.h"


TEST(TextGenTest, test1) {
    Text_Gen textgen;
    std::string filestring = "This is test";
    textgen.text_file(2, filestring);
    Text_Gen::prefix pref = { "This", "is" };

    EXPECT_EQ(textgen.statetab.begin()->first, pref);
}

TEST(TesxtGenTest, test2) {
    Text_Gen textgen;
    std::string filestring = "This is test";
    textgen.text_file(2, filestring);
    Text_Gen::prefix pref = { "This", "is" };
    EXPECT_EQ(textgen.statetab[pref][0], "test");
}

TEST(TextGenTest, test3) {
    Text_Gen textgen;
    std::string filestring = "Once I got stuck in an elevator";
    textgen.text_file(2, filestring);
    std::string res = textgen.text_generation(3, time(0));
    EXPECT_EQ(res, " Once I got ");
}

TEST(TextGenTest, test4) {
    Text_Gen textgen;
    std::string filestring = "an apple an orange";
    textgen.text_file(1, filestring);
    Text_Gen::prefix pref = { "an" };
    std::vector<std::string> suf = { "apple", "orange" };
    EXPECT_EQ(textgen.statetab[pref], suf);
}

TEST(TextGenTest, test5) {
    Text_Gen textgen;
    typedef std::deque<std::string> prefix;
    std::map<prefix, std::vector<std::string>> state = {
        { { "I" }, { "want" } },
        { { "want" }, { "sleep", "eat" } },
        { {"eat"}, {"apple"} }
    };
    textgen.statetab = state;
    std::string res = textgen.text_generation(4, 1);
    EXPECT_EQ(" ", res);
}
