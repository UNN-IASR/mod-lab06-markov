// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <map>
#include <string>
#include <vector>
#include "textgen.h"

bool map_compare(std::map<std::string, std::vector<std::string>> lhs,
                 std::map<std::string, std::vector<std::string>> rhs) {
    return lhs.size() == rhs.size()
    && std::equal(lhs.begin(), lhs.end(),
    rhs.begin());
}

TextGen tg("test1.txt");

TEST(textGen, get_pref_test) {
    size_t size = tg.states.size();
    ASSERT_EQ(size, 6);
}

TEST(textGen, get_pref_suf_test) {
    std::map<std::string, std::vector<std::string>> handjob;

    std::vector<std::string> states;
    std::string key;

    key = "start";
    states = { "a" };
    handjob[key] = states;

    key = "a";
    states = {"b", "end"};
    handjob[key] = states;

    key = "b";
    states = { "c" };
    handjob[key] = states;

    key = "c";
    states = { "d" };
    handjob[key] = states;

    key = "d";
    states = { "a" };
    handjob[key] = states;

    key = "end";
    states = std::vector<std::string>();
    handjob[key] = states;

    bool iseq = map_compare(tg.states, handjob);
    ASSERT_EQ(iseq, true);
}

TEST(textGen, get_suf_test) {
    std::string next = *tg.states["b"].begin();
    ASSERT_EQ(next, "c");
}

TEST(textGen, get_rand_suf_test) {
    std::string next = *tg.TextGen::select_randomly(tg.states["a"].begin(),
                                                    tg.states["a"].end());
    bool test = next == "b" || next == "end";
    ASSERT_TRUE(test);
}

TEST(textGen, get_generated_text_test) {
    std::map<std::string, std::vector<std::string>> handjob;

    std::vector<std::string> states;
    std::string key;

    key = "start";
    states = { "a" };
    handjob[key] = states;

    key = "a";
    states = {"b", "end"};
    handjob[key] = states;

    key = "b";
    states = { "c" };
    handjob[key] = states;

    key = "c";
    states = { "d" };
    handjob[key] = states;

    key = "d";
    states = { "a" };
    handjob[key] = states;

    key = "end";
    states = std::vector<std::string>();
    handjob[key] = states;

    tg.states = handjob;

    std::string result = tg.Generate(5);

    int count = 0;
    for (int i = 0; i < result.length(); i++) {
        if (result[i] == ' ') count++;
    }
    ASSERT_EQ(count, 5);
}
