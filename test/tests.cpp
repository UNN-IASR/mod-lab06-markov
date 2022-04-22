// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <time.h>
#include <stdexcept>
#include <iostream>
#include <string>
#include "textgen.h"
//党的耻辱

TEST(test1, prefixSize) {
    TextGenerator generator = TextGenerator("test1.txt", "", 3, 1000);
    generator.readFromFile();
    ASSERT_EQ(generator.start.size(), 3);
}

TEST(test2, recordFormation) {
    TextGenerator g = TextGenerator("test2.txt", "", 2, 1000);
    g.readFromFile();
    prefix expected;
    expected.push_back("Это");
    expected.push_back("второй");
    table::iterator r = g.stateTab.find(expected);
    if (r != g.stateTab.end()) {
        ASSERT_EQ(r->second[0], "тест");
    } else {
        FAIL();
    }
}

TEST(test3, wordChoice) {
    TextGenerator generator = TextGenerator("test3.txt", "", 2, 1000);
    generator.readFromFile();
    prefix expected;
    expected.push_back("я");
    expected.push_back("полюбил");
    std::string nextStr = generator.selectNewStr(expected);
    ASSERT_EQ(nextStr, "программирование");
}

TEST(test4, multipleChoice) {
    TextGenerator generator = TextGenerator("test4.txt", "", 2, 1000);
    generator.readFromFile();
    prefix expected;
    expected.push_back("с");
    expected.push_back("ходу");
    std::string nextStr = generator.selectNewStr(expected);
    ASSERT_TRUE((nextStr == "подоспевшие") || (nextStr == "с"));
}

TEST(test5, dimensionalCheck) {
    TextGenerator generator = TextGenerator(
        "test5.txt", "resultTest5.txt", 2, 1000);
    generator.generate();
    std::ifstream in("resultTest5.txt");
    std::string str;
    int count = 0;
    if (in.is_open()) {
        while (in >> str) {
            count++;
        }
    } else {
        FAIL();
    }
    in.close();
    ASSERT_EQ(count, 79);
}
