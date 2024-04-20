// Copyright 2024 Annenko Misha
#include <gtest/gtest.h>
#include "../include/textgen.h"

TEST(Test1, Prefix_formation) {
    textgen Markov_Chain;
    std::string input_text = "The cat lay down";

    int npref = 2;
    Markov_Chain.memorization(input_text, npref);

    textgen::prefix Prefix = { "The", "cat" };

    EXPECT_NE(Markov_Chain.statetab.find(Prefix), Markov_Chain.statetab.end());
}

TEST(Test2, Record_formation) {
    textgen Markov_Chain;
    std::string text = "The cat lay down";

    int npref = 2;
    Markov_Chain.memorization(text, npref);

    textgen::prefix Prefix = { "cat", "lay" };

    EXPECT_EQ(Markov_Chain.statetab[Prefix][0], "down");
}

TEST(Test3, A_single_suffix) {
    textgen Markov_Chain;
    std::string text = "The cat lay down";
    int npref = 2;
    int maxgen = 11;
    Markov_Chain.memorization(text, npref);

    std::string result = Markov_Chain.generate__text(maxgen, npref);
    for (int i = 0; i < 2; i++) {
        result.pop_back();
    }
    std::string requiredLine = "The cat lay";

    EXPECT_EQ(result, requiredLine);
}

TEST(Test4, Choosing_a_suffix) {
    textgen Markov_Chain;
    std::string text = "The cat is funny, The cat is sad, The cat is nervous";

    int npref = 2;
    int maxgen = 14;

    Markov_Chain.memorization(text, npref);
    std::string result = Markov_Chain.generate_text(maxgen, npref, 302);

    for (int i = 0; i < 2; i++) {
        result.pop_back();
    }
    std::string requiredLine = "The cat is nervous";

    EXPECT_EQ(result, requiredLine);
}

TEST(Test5, Manual_table) {
    textgen Markov_Chain;
    std::string text = "The cat is funny, The cat is sad, The cat is nervous";

    std::map<textgen::prefix, std::vector<std::string>> stateTable = {
        {{"The", "cat"}, {"is"}},
        {{"cat", "is"}, {"funny", "nervous"}},
        {{"is", "funny,"}, {"The"}},
        {{"funny,", "The"}, {"cat"}}
    };

    int npref = 2;
    int maxgen = 14;

    Markov_Chain.Manual_Table(stateTable);
    std::string result = Markov_Chain.generate_text(maxgen, npref, 302);

    for (int i = 0; i < 2; i++) {
        result.pop_back();
    }
    std::string requiredLine = "The cat is nervous";

    EXPECT_EQ(result, requiredLine);
}
