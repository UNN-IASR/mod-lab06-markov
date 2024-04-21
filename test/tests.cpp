// Copyright 2024 Alexander Sidelnikov

#include <gtest/gtest.h>
#include "textgen.h"

TEST(textgen, prefix_with_specified_number_of_words) {
    int prefix_size = 2;
    TextGenerator generator(prefix_size);
    std::istringstream input("some words go here");

    generator.create_suffix_map(input);

    auto map = generator.get_suffix_map();
    for (auto prefix : map) {
        EXPECT_EQ(prefix_size, prefix.first.size());
    }
}

TEST(textgen, create_prefixsuffix_map) {
    int prefix_size = 2;
    TextGenerator generator(prefix_size);
    std::istringstream input("some words go here");

    generator.create_suffix_map(input);

    auto map = generator.get_suffix_map();
    EXPECT_EQ(2, map.size());
}

TEST(textgen, choose_single_suffix) {
    int prefix_size = 2;
    TextGenerator generator(prefix_size, 1);
    std::istringstream input("some words go here");
    generator.create_suffix_map(input);

    auto result = generator.generate(3);

    std::string expected = "some words go ";
    EXPECT_EQ(expected, result);
}

TEST(textgen, choose_suffix_from_multiple) {
    int prefix_size = 2;
    TextGenerator generator(prefix_size, 1);
    std::istringstream input("Aome Bords Co Aome Bords Dot");
    generator.create_suffix_map(input);

    auto result = generator.generate(3);

    std::string expected = "Aome Bords Dot ";
    EXPECT_EQ(expected, result);
}

TEST(textgen, generate_text_with_given_table) {
    int prefix_size = 1;
    TextGenerator generator(prefix_size, 1);
    std::map<prefix, std::vector<std::string>> map = {
        { { "Some" }, { "words" } },
        { { "words" }, { "more", "less" } },
        { { "more" }, { "likely" } },
        { { "less" }, { "likely" } },
    };
    generator.create_suffix_map(map);

    auto result = generator.generate(4);

    std::string expected = "Some words less likely ";
    EXPECT_EQ(expected, result);
}
