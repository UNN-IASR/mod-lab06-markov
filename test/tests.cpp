// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"

TEST(task1, test1) {
    MarkovGenerator gen = MarkovGenerator("test.txt", NPREF);
    int result = gen.getPrefixSize();
    EXPECT_EQ(2, result);
}

TEST(task2, test2) {
    MarkovGenerator gen = MarkovGenerator("test.txt", NPREF);
    std::deque<std::string> newPrefixes {"rock", "spewed"};
    std::string newSuffix = gen.getSuffix(newPrefixes);
    EXPECT_EQ("forth", newSuffix);
}

TEST(task3, test3) {
    MarkovGenerator gen = MarkovGenerator("test.txt", NPREF);
    std::deque<std::string> newPrefixes {"corpses", "buried"};
    std::string newSuffix = gen.getSuffix(newPrefixes);
    EXPECT_EQ("for", newSuffix);
}

TEST(task4, test4) {
    MarkovGenerator gen = MarkovGenerator("test.txt", NPREF);
    std::deque<std::string> newPrefixes {"things", "worth"};
    std::string newSuffix = gen.getSuffix(newPrefixes);
    EXPECT_TRUE(newSuffix == "dying" || newSuffix == "living");
}

TEST(task5, test5) {
    MarkovGenerator gen = MarkovGenerator("test.txt", NPREF);
    std::string text = gen.getText(MAXGEN);
    int counter = 0;
    for (int i = 0; i < text.size(); i++) {
        if (text[i] == ' ') counter++;
    }
    EXPECT_LE(counter, MAXGEN + 1);
}
