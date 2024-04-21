// Copyright 2024 StatsenkoArs

#include <gtest/gtest.h>
#include "textgen.h"

TEST(gen_prefix, test1) {
    Markov chain;
    std::string in = "The difference between stupidity"
        " and genius is that genius has its limits.";
    std::vector<std::string> words = chain.mySplit(in, ' ');
    int len = 3;
    int pos = 4;
    prefix pre = chain.gen_pre(words, pos, len);
    for (int i = 0; i < len; i++)
        EXPECT_EQ(words[pos - len + i], pre.at(i));
}

TEST(gen_prefix_suffix, test2) {
    Markov chain;
    std::string in = "The difference between stupidity"
        " and genius is that genius has its limits.";
    chain.gen_tab(in, 11);
    prefix key({ "The", "difference", "between", "stupidity",
        "and", "genius", "is", "that", "genius", "has", "its" });
    std::vector<std::string> value{ "limits." };
    for (const auto& el : chain.statetab) {
        EXPECT_EQ(key, el.first);
        EXPECT_EQ(value, el.second);
    }
}

TEST(pick_suffix, test3) {
    Markov chain;
    std::string in = "The difference between";
    chain.gen_tab(in, 2);
    prefix pre({ "The", "difference" });
    std::string text = chain.pick_next(pre);
    ASSERT_TRUE((text == "between") || (text == "burgers"));
}

TEST(pick_single_suffix, test4) {
    Markov chain;
    std::string in = "The difference between The difference burgers";
    chain.gen_tab(in, 2);
    prefix pre({ "The", "difference" });
    std::string text = chain.pick_next(pre);
    ASSERT_TRUE((text == "between") || (text == "burgers"));
}

TEST(gen_all_text, test5) {
    Markov chain;
    chain.statetab = {
        { { "a", "b" }, { "c", "d" } },
        { { "1", "2" }, { "3" }}
    };
    std::string text = chain.gen_text(3);
    ASSERT_TRUE((text == "1 2 3 ")
        || (text == "a b c ")
        || (text == "a b d "));
}
