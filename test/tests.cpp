// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>

#include "textgen.h"

TEST(TextGenTest, PrefixTwoWords) {
    TextGenerator generator_markova;
    prefix pref = {"AA", "BB"};
    generator_markova.add_pref(pref, "CC");
    ASSERT_EQ("CC", generator_markova.random_suff(pref));
}

TEST(TextGenTest, PrefixThreeWords) {
    TextGenerator generator_markova;
    prefix pref = {"AA", "BB", "CC"};
    generator_markova.add_pref(pref, "D");
    ASSERT_EQ(generator_markova.random_suff(pref).size(), 1);
}

TEST(TextGenTest, SingleSuffix) {
    TextGenerator generator_markova;
    generator_markova.add_pref({"AA"}, "BB");
    EXPECT_EQ(generator_markova.random_suff({"AA"}), "BB");
}

TEST(TextGenTest, MultipleSuffixes) {
    TextGenerator generator_markova;
    generator_markova.add_pref({"AA"}, "Z");
    generator_markova.add_pref({"AA"}, "V");

    std::string result = generator_markova.random_suff({"AA"});
    EXPECT_TRUE(result == "Z" || result == "V");
}

TEST(TextGenTest, TextLength) {
    TextGenerator generator_markova;
    generator_markova.add_pref({"AA", "BB", "CC"}, "DD");
    generator_markova.add_pref({"CC", "DD", "EE"}, "FF");

    generator_markova.generate_text(OUTPUT_FILE_PATH, 4);
    std::ifstream file(OUTPUT_FILE_PATH);
    int wordCount = 0;
    std::string word;

    while (file >> word) wordCount++;
    EXPECT_EQ(wordCount, 4);
}

TEST(TextGenTest, EmptyInput) {
    TextGenerator generator_markova;
    EXPECT_THROW(
        generator_markova.generate_text(OUTPUT_FILE_PATH, 1000),
        std::runtime_error
    ) << "Should throw exception for invalid file path";
}
