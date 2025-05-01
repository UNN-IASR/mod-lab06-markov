// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include<string>
#include<vector>
#include<map>
#include<deque>
#include<queue>
#include "textgen.h"

typedef std::deque<std::string> prefix;

TEST(CreatePrefix, test1) {
    prefix pref;
    pref.push_back("word1");
    pref.push_back("word2");
    EXPECT_EQ(pref.front(), "word1");
    EXPECT_EQ(pref.back(), "word2");
}

TEST(CreatePrefix, test2) {
    prefix pref;
    pref.push_back("word1");
    pref.push_back("word2");
    EXPECT_NE(pref.front(), "word2");
    EXPECT_NE(pref.back(), "word1");
}

TEST(CreateSuffix, test1) {
    std::map<prefix, std::vector<std::string>> table;
    prefix pref{"word1", "word2"};
    table[pref].push_back("word3");
    EXPECT_EQ(table[pref][0], "word3");
}

TEST(CreateSuffix, test2) {
    std::map<prefix, std::vector<std::string>> table;
    prefix pref{"word1", "word2"};
    table[pref].push_back("word3");
    table[pref].push_back("word4");
    EXPECT_EQ(table[pref][0], "word3");
    EXPECT_EQ(table[pref][1], "word4");
}

TEST(CreateSuffix, test3) {
    std::map<prefix, std::vector<std::string>> table;
    prefix pref{"word1", "word2"};
    table[pref].push_back("word3");
    table[pref].push_back("word4");
    int ind = 0;
    EXPECT_TRUE(table[pref][ind] == "word3" || table[pref][ind] == "word4");
}

TEST(GenerateTest, test1) {
    std::map<prefix, std::vector<std::string>> table {
        {{"a", "a"}, {"a"}}
    };

    TextGen generator(table);
    std::string name = "test.txt";
    generator.Generate(name, time(0), 10);
    std::ifstream in("../result/" + name);
    if (in.is_open()) {
        std::string str;
        while (!in.eof()) {
            in >> str;
            EXPECT_EQ(str, "a");
        }
    }
    in.close();
}

TEST(GenerateTest, test2) {
    std::map<prefix, std::vector<std::string>> table {
        {{"a", "b"}, {"c"}},
        {{"b", "c"}, {"a"}},
        {{"c", "a"}, {"b"}}
    };
    std::vector<std::string> ans = {"a", "b", "c"};

    TextGen generator(table);
    std::string name = "test.txt";
    int cntWords = 12;
    generator.Generate(name, time(0), cntWords);
    std::ifstream in("../result/" + name);
    if (in.is_open()) {
        int cnt = 0;
        std::string str;
        while (!in.eof() && cntWords--) {
            in >> str;
            EXPECT_EQ(str, ans[cnt % 3]);
            cnt++;
        }
    }
    in.close();
}

TEST(GenerateTest, test3) {
    std::map<prefix, std::vector<std::string>> table {
        {{"a", "a"}, {"a", "a"}}
    };

    TextGen generator(table);
    std::string name = "test3.txt";
    int cntWords = 15;
    generator.Generate(name, time(0), cntWords);
    std::ifstream in("../result/" + name);
    int cnt = -1;
    if (in.is_open()) {
        std::string str;
        while (!in.eof()) {
            in >> str;
            cnt++;
        }
    }
    in.close();

    EXPECT_EQ(cntWords, cntWords);
}

TEST(GenerateTest, test4) {
    std::string name = "blabla.txt";
    ASSERT_THROW(TextGen generator(name), std::runtime_error);
}

TEST(GenerateTest, test5) {
    std::string name = "blabla.txt";
    try {
        TextGen generator(name);
        FAIL();
    }
    catch( const std::runtime_error& err ) {
        ASSERT_STREQ("incorrect name of file", err.what());
    }
}
