// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "../include/textgen.h"
typedef std::deque<std::string> prefix;
TEST(Test, Test_1) {
    std::vector<std::string> words = {"today", "is", "a", "good", "day"};
    generator gen;
    std::map<prefix, std::vector<std::string>> tablica =
      gen.sozdaem_tablicu(words);
    prefix p = gen.prefixi(tablica);
    std::string a = "";
    for (auto word : p) {
        a += word + ' ';
    }
    EXPECT_EQ(a, "today is ");
}
TEST(Test, Test_2) {
    std::vector<std::string> words = {"today", "is", "a", "good", "day"};
    generator gen;
    std::map<prefix, std::vector<std::string>> tablica =
      gen.sozdaem_tablicu(words);
    prefix p = gen.prefixi(tablica);
    std::string a = "";
    for (auto word : p) {
        a += word + ' ';
    }
    std::string j = gen.suffix_poick(p, tablica);
    std::string res = a + j;
    EXPECT_EQ(res, "today is a");
}
TEST(Test, Test_3) {
    std::vector<std::string> words = {"today", "is", "a"};
    generator gen;
    std::map<prefix, std::vector<std::string>> tablica =
      gen.sozdaem_tablicu(words);
    prefix p = gen.prefixi(tablica);
    std::string suffix = gen.suffix_poick(p, tablica);
    EXPECT_EQ(suffix, "a");
}
TEST(Test, Test_4) {
    std::vector<std::string> words = {"today", "is", "a", "good", "day"};
    generator gen;
    std::map<prefix, std::vector<std::string>> tablica =
      gen.sozdaem_tablicu(words);
    prefix p = gen.prefixi(tablica);
    std::string suffix = gen.suffix_poick(p, tablica);
    EXPECT_EQ(suffix, "a");
}
TEST(Test, Test_5) {
    generator gen;
    std::map<prefix, std::vector<std::string>> tablica = {
        {{"good", "day"}, {"!!!"}},
        {{"is", "good"}, {"day"}},
        {{"today", "is"}, {"good"}}
    };
    gen.MAXGEN = 4;
    std::string res = gen.itogovii_text(tablica);
    EXPECT_EQ(res, "today is good good ");
}
