// Copyright 2024 RuzKate

#include <gtest/gtest.h>
#include <string>
#include "../include/textgen.h"

TEST(test1, PrefixFormation) {
    MarkovGenerator markovGenerator;

    std::string text = "Lorem ipsum dolor";

    markovGenerator.CreateTable(text, 2);
    Prefix prefix = {"Lorem", "ipsum"};

    std::map<Prefix, std::vector<std::string>> tab = markovGenerator.getTab();
    EXPECT_NE(tab.find(prefix), tab.end());
}

TEST(test2, CheckSuffix) {
    MarkovGenerator markovGenerator;

    std::string text = "Lorem ipsum dolor sit amet";

    markovGenerator.CreateTable(text, 2);
    Prefix prefix = {"Lorem", "ipsum"};

    std::map<Prefix, std::vector<std::string>> tab = markovGenerator.getTab();
    EXPECT_NE(tab.at(prefix)[0], "dolor ");
}

TEST(test3, SingleSuffixSelection) {
    MarkovGenerator markovGenerator;

    std::string text = "Lorem ipsum dolor sit amet,";
                text += "consectetuer adipiscing elit at.";

    markovGenerator.CreateTable(text, 2);
    std::string gen = markovGenerator.Generate(18, 10);

    EXPECT_EQ(gen, "Lorem ipsum dolor");
}

TEST(test4, ManySuffixes) {
    MarkovGenerator markovGenerator;

    std::string text = "Lorem ipsum dolor sit amet,";
                text += "consectetuer adipiscing elit.";

    Prefix prefix = { "ipsum" };
    std::vector<std::string> suffix = { "dolor" };

    markovGenerator.CreateTable(text, 1);

    EXPECT_EQ(suffix, markovGenerator.getTab().at(prefix));
}

TEST(test5, TextFormation) {
    MarkovGenerator markovGenerator;

    std::string text = "Lorem ipsum dolor sit amet,";
                text += "consectetuer adipiscing elit";
                text += "aenean commodo ligula eget";

    std::map<Prefix, std::vector<std::string>> statetab = {
        {{"Lorem", "ipsum"}, {"dolor"}},
        {{"ipsum", "dolor"}, {"sit", "eget"}},
        {{"dolor", "sit"}, {"Lorem"}},
        {{"sit", "amet"}, {"ipsum"}}
    };

    markovGenerator.trainFromStateTable(statetab);
    std::string result = markovGenerator.Generate(18, 100);

    EXPECT_EQ(result, "Lorem ipsum dolor");
}
