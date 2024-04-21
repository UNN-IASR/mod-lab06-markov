// Copyright 2024 Vladislav Labutin

#include <gtest/gtest.h>
#include "textgen.h"

TEST(test1, form_prefix) {
    markov generator;
    generator.train("test/test1.txt", 2);
    markov::prefix pref = {"one", "two"};
    EXPECT_EQ(pref, generator.table.begin()->first);
}

TEST(test2, form_prefix_suffix) {
    markov generator;
    generator.train("test/test1.txt", 2);
    markov::prefix pref = {"one", "two"};
    markov::suffixes suffs = {"three"};
    EXPECT_EQ(suffs, generator.table[pref]);
}

TEST(test3, chose_one_suffix) {
    markov generator;
    generator.train("test/test2.txt", 1);
    EXPECT_EQ("five one two three ", generator.generate(4, false));
}

TEST(test4, chose_sev_suffix) {
    markov generator;
    generator.train("test/test3.txt", 1);
    std::string result = generator.generate(2, false);
    ASSERT_TRUE(result == "alien cat, " ||
                result == "alien dog, " ||
                result == "alien cow ");
}

TEST(test5, form_text_hand_table) {
    markov generator;
    std::map<markov::prefix, markov::suffixes> table = {
        {{"alien"}, {"cat"}},
        {{"cat"}, {"goes"}},
        {{"goes"}, {"meow", "bark bark"}}
    };
    generator.table = table;
    std::string result = generator.generate(3, true);
    ASSERT_TRUE(result == "alien cat goes " ||
                result == "cat goes meow " ||
                result == "cat goes bark bark " ||
                result == "goes meow " ||
                result == "goes bark bark ");
}
