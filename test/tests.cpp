// Copyright 2024 Shelnov Yuriy
#include <gtest/gtest.h>

#include "textgen.h"
TEST(task1, test1) {
    TextGenerator Tg = TextGenerator("test.txt", 2);
    int result = Tg.getCurrentPrefixLength();
    EXPECT_EQ(2, result);
}

TEST(task2, test2) {
    TextGenerator Tg = TextGenerator("test.txt", 2);
    std::deque<std::string> new2ixes{"rock", "spewed"};
    std::string newSuffix = Tg.getSuffix(new2ixes);
    EXPECT_EQ("forth", newSuffix);
}

TEST(task3, test3) {
    TextGenerator  Tg = TextGenerator("test.txt", 2);
    std::deque<std::string> new2ixes {"corpses", "buried"};
    std::string newSuffix = Tg.getSuffix(new2ixes);
    EXPECT_EQ("for", newSuffix);
}

TEST(task4, test4) {
    TextGenerator Tg = TextGenerator("test.txt", 2);
    std::deque<std::string> new2ixes {"things", "worth"};
    std::string newSuffix = Tg.getSuffix(new2ixes);
    EXPECT_TRUE(newSuffix == "dying" || newSuffix == "living");
}

TEST(task5, test5) {
    TextGenerator Tg = TextGenerator("test.txt", 2);
    std::string text = Tg.getText(1000);
    int counter = 0;
    for (int i = 0; i < text.size(); i++) {
        if (text[i] == ' ') counter++;
    }
    EXPECT_LE(counter, 1000 + 1);
}
