// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "../include/textgen.h"

TEST(task1, test1) {
    TextGenerator tg = TextGenerator("test1.txt");
    tg.read();
    tg.get_words();
    ASSERT_EQ(tg.prefixes.size(), tg.vector_words.size());
}

TEST(task2, test1) {
    TextGenerator tg = TextGenerator("test2.txt");
    tg.read();
    tg.get_words();
    tg.make_dictionary();
    tg.get_connected();
    typedef std::deque<std::string> prefix;
    prefix values;
    values.push_back(tg.prefixes[0]);
    values.push_back(tg.prefixes[1]);
    ASSERT_EQ(tg.statetab.at(values), tg.suffix[0]);
}

TEST(task3, test1) {
    TextGenerator tg = TextGenerator("test3.txt");
    std::string text = "The report led to a huge backlash on social media";
    text+=" and support for the Labour deputy leader.";
    tg.vector_words.push_back(tg.get_list(text));
    for (int i = 0; i < tg.vector_words.size(); i++) {
        tg.prefixes.push_back(tg.vector_words[i]);
    }
    typedef std::deque<std::string> prefix;
    prefix values;
    tg.make_dictionary();
    tg.get_connected();
    values.push_back(tg.prefixes[0]);
    values.push_back(tg.prefixes[1]);
    ASSERT_EQ(tg.statetab.at(values)[0], tg.suffix[0][0]);
}

TEST(task4, test1) {
    TextGenerator tg = TextGenerator("test4.txt");
    typedef std::deque<std::string> prefix;
    prefix values;
    std::string text = "Hello, my dear! Hello, my lovely! Hello ";
    text += "my beautiful!";
    tg.vector_words.push_back(tg.get_list(text));
    for (int i = 0; i < tg.vector_words.size(); i++) {
        tg.prefixes.push_back(tg.vector_words[i]);
    }
    tg.make_dictionary();
    tg.get_connected();
    values.push_back(tg.prefixes[1]);
    values.push_back(tg.prefixes[2]);
    ASSERT_TRUE((tg.statetab.at(values)[0] == tg.suffix[1][0])
        || (tg.statetab.at(values)[0] == tg.suffix[1][1])
        || (tg.statetab.at(values)[0] == tg.suffix[1][2]));
}

TEST(task5, test1) {
    TextGenerator tg = TextGenerator("test5.txt");
    std::string text = "The Mail on Sunday is not commenting.";
    tg.vector_words.push_back(tg.get_list(text));
    for (int i = 0; i < tg.vector_words.size(); i++) {
        tg.prefixes.push_back(tg.vector_words[i]);
    }
    typedef std::deque<std::string> prefix;
    prefix values;
    tg.make_dictionary();
    tg.get_connected();
    values.push_back(tg.prefixes[0]);
    values.push_back(tg.prefixes[1]);
    ASSERT_EQ(tg.statetab.at(values)[0], tg.suffix[0][0]);
}
