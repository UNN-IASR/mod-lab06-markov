// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"

TEST(test1, setPrefix) {
    std::string str("If at first you don't succeed then try, try again.");
    std::stringstream sstr1(str);
    TextGen generator1(sstr1, 1);
    TextGen::prefix prefix1 = { "you" };
    EXPECT_NE(generator1.states().find(prefix1), generator1.states().end());
    std::stringstream sstr5(str);
    TextGen generator5(sstr5, 5);
    TextGen::prefix prefix5 = { "you", "don't", "succeed", "then", "try," };
    EXPECT_NE(generator5.states().find(prefix5), generator5.states().end());
}

TEST(test2, checkSuffix) {
    std::string str("If at first you don't succeed then try, try again.");
    std::stringstream sstr(str);
    TextGen generator(sstr, 5);
    TextGen::prefix prefix = { "you", "don't", "succeed", "then", "try," };
    EXPECT_EQ(generator.states().at(prefix)[0], "try");
}

TEST(test3, pickSingle) {
    std::string str("1 2 3 4 5");
    std::stringstream sstr(str);
    TextGen generator(sstr, 1);
    std::string output = generator.CreateText(20, 1);
    EXPECT_EQ(output, "1 2 3 4 5 \n");
}

TEST(test4, pickMultiple) {
    std::string str("1 2 3 4 1 2 3 5 1 2 3 6 1 2 3 7");
    std::stringstream sstr(str);
    TextGen generator(sstr, 1);
    std::string output = generator.CreateText(10, 1);
    EXPECT_EQ(output, "1 2 3 7 \n");
}

TEST(test5, handwrittenTable) {
    std::map<TextGen::prefix, std::vector<std::string>> map;
    TextGen::prefix pr1 = { "0", "1" };
    map[pr1] = { "2" };
    TextGen generator(map);
    std::string output = generator.CreateText(1000);
    EXPECT_LT(output.size(), 10);
}
