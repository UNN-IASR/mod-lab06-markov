// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <time.h>
#include <stdexcept>
#include <iostream>
#include <string>
#include "textgen.h"


TEST(test1, prefix_check_1) {
    TextGenerator tg = TextGenerator("test1_2.txt");
    tg.read_from_file();
    tg.get_words();
    ASSERT_EQ(tg.prefixes.size(), tg.slova.size());
}

TEST(test2, prefix_suffix_1) {
    TextGenerator tg = TextGenerator("test1_2.txt");
    tg.read_from_file();
    tg.get_words();
    tg.find_suffix();
    tg.get_connected();
    typedef std::deque<std::string> prefix;
    prefix values;
    values.push_back(tg.prefixes[0]);
    values.push_back(tg.prefixes[1]);
    ASSERT_EQ(tg.statetab.at(values), tg.suffix[0]);
}

TEST(test3, one_suffix) {
    TextGenerator tg = TextGenerator("test1_2.txt");
    std::string text = "I'm a student of university in Niznhy Novgorod";
    tg.slova.push_back(tg.get_list_of_strings(text));
    for (int i = 0; i < tg.slova.size(); i++) {
        tg.prefixes.push_back(tg.slova[i]);
    }
    typedef std::deque<std::string> prefix;
    prefix values;
    tg.find_suffix();
    tg.get_connected();
    values.push_back(tg.prefixes[0]);
    values.push_back(tg.prefixes[1]);
    ASSERT_EQ(tg.statetab.at(values)[0], tg.suffix[0][0]);
}

TEST(test4, some_suffixes) {
    TextGenerator tg = TextGenerator("test1_2.txt");
    typedef std::deque<std::string> prefix;
    prefix values;
    std::string text = "Hello, my dear! Hello, my lovely! Hello ";
    text += "my beautiful!";
    tg.slova.push_back(tg.get_list_of_strings(text));
    for (int i = 0; i < tg.slova.size(); i++) {
        tg.prefixes.push_back(tg.slova[i]);
    }
    tg.find_suffix();
    tg.get_connected();
    values.push_back(tg.prefixes[1]);
    values.push_back(tg.prefixes[2]);
    ASSERT_TRUE((tg.statetab.at(values)[0] == tg.suffix[1][0])
    || (tg.statetab.at(values)[0] == tg.suffix[1][1])
    || (tg.statetab.at(values)[0] == tg.suffix[1][2]));
}

TEST(test5, generate_from_table) {
    TextGenerator tg = TextGenerator("test1_2.txt");
    std::string text;
    text = "Раз, два, три, четыре, пять, Вышел зайчик погулять. ";
    text += "Вдруг охотник выбегает, Прямо в зайчика стреляет. ";
    text += "Но охотник не попал, Серый зайчик убежал.";
    tg.slova.push_back(tg.get_list_of_strings(text));
    for (int i = 0; i < tg.slova.size(); i++) {
        tg.prefixes.push_back(tg.slova[i]);
    }
    tg.find_suffix();
    tg.get_connected();
    std::string result = tg.get_result(25);
    int i = -1, index = 0;
    while (result.find(' ', index) != -1) {
        index = result.find(' ', index + 1);
        i++;
    }
    ASSERT_LE(i, 25);
}
