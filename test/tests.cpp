// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"

TEST(prefix_count, first) {
    auto table = Generator().GenerateTable(2, "fist second third");
    for (const auto& element : table) {
        EXPECT_EQ(element.first.size(), 2);
    }
}

TEST(prefix_suffix_pair, pair) {
    auto table = Generator().GenerateTable(2, "first second third");
    suffix suf = table.begin()->second;
    EXPECT_EQ(suf[0], "third");
}

TEST(prefix_suffix_pair, one_suffix) {
    auto table = Generator().GenerateTable(1, "first second");
    suffix suf = table.begin()->second;
    EXPECT_EQ(suf[0], "second");
}

TEST(prefix_suffix_pair, many_suffix) {
    auto table = Generator().GenerateTable(1, "first second third");
    prefix pr1 = prefix{"first"};
    prefix pr2 = prefix{"second"};
    EXPECT_EQ(table[pr1][0], "second");
    EXPECT_EQ(table[pr2][0], "third");
}

TEST(text_generate, with_length) {
    std::string text = "lorem ipsum dolor sit amet lorem ipsum";
    std::string result = Generator().GenerateText(text, 2, 30);

    EXPECT_LE(Split(result, " ").size(), 30);
}
