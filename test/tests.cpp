// Copyright 2024 Ignatyev Artyom

#include <gtest/gtest.h>
#include <textgen.h>

TEST(test1, prefix) {
    Generator gen;
    std::istringstream str("car train ship");
    gen.createStatetab(str, 2);
    std::map<Prefix, std::vector<std::string>> map = gen.getStatetab();
    Prefix exp = { "car", "train" };
    EXPECT_EQ(exp, map.begin()->first);
}

TEST(test2, suffix) {
    Generator gen;
    std::istringstream str("car train ship");
    gen.createStatetab(str, 2);
    std::map<Prefix, std::vector<std::string>> map = gen.getStatetab();
    std::vector<std::string> exp = { "ship" };
    EXPECT_EQ(exp, map.begin()->second);
}

TEST(test3, single) {
    Generator gen;
    std::map<Prefix, std::vector<std::string>> statetab1;
    statetab1[{ "prefix" }] = { "suffix" };
    gen.setStatetab(statetab1);
    std::string text1 = gen.generateText(2);
    EXPECT_EQ(text1, "prefix suffix ");
}

TEST(test4, multiple) {
    Generator gen;
    std::map<Prefix, std::vector<std::string>> statetab2;
    statetab2[{ "prefix" }] = { "suffix1", "suffix2" };
    gen.setStatetab(statetab2);
    std::string text2 = gen.generateText(2);
    EXPECT_TRUE(text2 == "prefix suffix1 " || text2 == "prefix suffix2 ");
}

TEST(test5, custom_table) {
    Generator gen;
    std::map<Prefix, std::vector<std::string>> map = {
        { { "bag" }, { "sun" } },
        { { "egg" }, { "war" } },
    };
    gen.setStatetab(map);
    std::string res = gen.generateText(2);
    EXPECT_EQ(8, res.size());
}
