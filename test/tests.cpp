// Copyright 2022 GHA Test Team
#include <gtest/gtest.h>

#include "textgen.h"

TEST(AllTests, Prefix) {
    std::vector<std::string> text = {"hello", "again", "my", "friend"};

    std::set<std::deque<std::string>> expected_prefixes = {
        {"hello", "again"}, {"again", "my"}, {"my", "friend"}
    };

    text_generator tg{2};
    tg.power_up(text);
    auto base = tg.get_base();

    std::set<std::deque<std::string>> actual_prefixes;
    for (auto& x : base) {
        actual_prefixes.insert(x.first);
    }

    ASSERT_EQ(expected_prefixes.size(), actual_prefixes.size());
    for (auto& x : expected_prefixes) {
        ASSERT_TRUE(actual_prefixes.find(x) != actual_prefixes.end());
    }
}

TEST(AllTests, Suffix) {
    std::vector<std::string> text = {"hello", "again", "my", "friend"};

    text_generator tg{2};
    tg.power_up(text);
    auto base = tg.get_base();

    std::deque<std::string> list {"my"};
    auto iterator = base[std::deque<std::string>{"hello", "again"}].begin();
    for (auto& x : list) {
        ASSERT_EQ(iterator->first, x);
        ++iterator;
    }
}

TEST(AllTests, SuffixMulti) {
    std::vector<std::string> text =
    { "hello", "again", "my", "friend", "hello", "again", "darling"};

    text_generator tg{2};
    tg.power_up(text);
    auto base = tg.get_base();

    std::deque<std::string> list {"darling", "my"};
    auto iterator = base[std::deque<std::string>{"hello", "again"}].begin();
    for (auto& x : list) {
        ASSERT_EQ(iterator->first, x);
        ++iterator;
    }
}

TEST(AllTests, TextGeneration) {
    std::vector<std::string> text =
    {"hello", "again", "my", "friend", "hello", "again", "darling"};

    text_generator tg{3};
    tg.power_up(text);
    std::string out = tg.generate_text(10, 5);
    ASSERT_EQ(out[out.length()-1], '.');
}
