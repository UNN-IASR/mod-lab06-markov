// Copyright 2024 Kapochkin Mikhail
#include <gtest/gtest.h>
#include "../include/textgen.h"
TEST(Test1, CheckPrefixInText) {
    TextGen textgen;
    textgen.CreateStatetabPrefixes("Hello world Russia, my name is Mikhail", 2);
    std::map<prefix, std::vector<std::string>> statetab = textgen.get();
    prefix pref = { "Hello", "world" };
  EXPECT_EQ(pref, statetab.begin()->first);
}
TEST(Test2, PrefixSuffixConstruction) {
    TextGen textgen;
    textgen.CreateStatetabPrefixes("Hello world, mates!", 2);
    prefix prefix = { "Hello", "world," };
    EXPECT_EQ(textgen.get().at(prefix)[0], "mates!");
}

TEST(Test3, IfOneSuffix) {
    TextGen textgen;
    textgen.CreateStatetabPrefixes("one two 3 four 5 two 11 12", 1);
    std::string generated_string = textgen.GenerateText(time(0), 5);
    std::cout << generated_string;
    EXPECT_EQ(generated_string, "one two 3 four 5 ");
}

TEST(Test4, IfNotOneSuff) {
    TextGen textgen;
    textgen.CreateStatetabPrefixes("one two 3 four 5 two 11 12", 1);
    prefix pref = { "two" };
    std::vector<std::string> suffix = { "3", "11" };
    EXPECT_EQ(suffix, textgen.get().at(pref));
}

TEST(test5, textCreationForNoPref) {
    TextGen textgen;
    std::map<prefix, std::vector<std::string> > str1 = {
        { { "1" }, { "2"} },
        { { "2" }, { "fail", "promise" } },
        { { "fail" }, { "moment", "value"}}
    };
    textgen.set(str1);
    std::string str = textgen.GenerateText(time(0), 20);
    EXPECT_EQ("", str);
}
